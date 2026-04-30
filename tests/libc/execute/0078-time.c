#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
output:
testing
50592 dates compared, all OK
done
end:
*/


#ifndef __unix__
#define putenv(x) (x)
/*
 * Ok, this is by definition undefined behaviour because
 * we are using the name of a library function. The reallity
 * is that if you use a static linker then this would
 * overload the libc getenv and it will work as expected,
 * but if you use a dynamic linker then the internal
 * references will be tied to the internal getenv function
 * and this would not work. For our main use case that is
 * testing scc libc this is good enough, and with the
 * fallback to putenv and unsetenv this will work in
 * the systems we are interested on
 */
char *
getenv(const char *name)
{
	if (strcmp(name, "TZ") != 0)
		return NULL;
	return "UTC";
}
#endif

static long long
datetounix(long long year, int mon, int day, int hour, int min, int sec)
{
	/* seconds in a month in a regular (non-leap) year */
	static const long secs_through_month[] = {
		0, 31 * 86400, 59 * 86400, 90 * 86400,
		120 * 86400, 151 * 86400, 181 * 86400, 212 * 86400,
		243 * 86400, 273 * 86400, 304 * 86400, 334 * 86400 };
	int is_leap = 0, cycles, centuries = 0, leaps = 0, rem;
	long long t;

	/* optimization: handle common range year 1902 up to and including 2038 */
	if (year - 2ULL < 136) {
		/* amount of leap days relative to 1970: every 4 years */
		leaps = (year - 68) >> 2;
		if (!((year - 68) & 3)) {
			leaps--;
			is_leap = 1;
		} else {
			is_leap = 0;
		}
		t = 31536000 * (year - 70) + (86400 * leaps); /* 365 * 86400 = 31536000 */
	} else {
		/* general leap year calculation:
		   leap years occur mostly every 4 years but every 100 years
		   a leap year is skipped unless the year is divisible by 400 */
		cycles = (year - 100) / 400;
		rem = (year - 100) % 400;
		if (rem < 0) {
			cycles--;
			rem += 400;
		}
		if (!rem) {
			is_leap = 1;
		} else {
			if (rem >= 300) {
				centuries = 3;
				rem -= 300;
			} else if (rem >= 200) {
				centuries = 2;
				rem -= 200;
			} else if (rem >= 100) {
				centuries = 1;
				rem -= 100;
			}
			if (rem) {
				leaps = rem / 4U;
				rem %= 4U;
				is_leap = !rem;
			}
		}
		leaps += (97 * cycles) + (24 * centuries) - is_leap;

		/* adjust 8 leap days from 1970 up to and including 2000:
		   ((30 * 365) + 8) * 86400 = 946771200 */
		t = ((year - 100) * 31536000LL) + (leaps * 86400LL) + 946771200LL;
	}
	t += secs_through_month[mon];
	if (is_leap && mon >= 2)
		t += 86400;
	t += 86400LL * (day - 1);
	t += 3600LL * hour;
	t += 60LL * min;
	t += sec;

	return t;
}

void
testtm(struct tm *tm)
{
	time_t t1, t2; /* assume time_t is signed 64-bit */
	long long ll;

	t1 = mktime(tm);
	if (t1 == (time_t)-1) {
		printf("timegm failed for %d, %d, %d, %d, %d, %d\n",
			tm->tm_year, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
	}

	ll = datetounix(tm->tm_year, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
	t2 = (time_t)ll;

	if (t1 != t2) {
		printf("result: %lld != %lld\n", (long long)t1, (long long)t2);
		printf("for: %d, %d, %d, %d, %d, %d\n",
			tm->tm_year, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
		exit(1);
	}
}

int
main(void)
{
	struct tm tm;
	int y, mon, d;
	unsigned counter = 0;

	puts("testing");
	putenv("TZ=UTC");

	for (y = 1902; y < 2038; y++) {
		for (mon = 0; mon < 12; mon++) {
			for (d = 1; d <= 31; d++) {

				memset(&tm, 0, sizeof(tm));
				tm.tm_year = y - 1900;
				tm.tm_mon = mon - 1;
				tm.tm_mday = d;
				tm.tm_hour = 0;
				tm.tm_min = 0;
				tm.tm_sec = 0;
				tm.tm_isdst = -1;

				testtm(&tm);
				counter++;
			}
		}
	}
	printf("%u dates compared, all OK\n", counter);
	puts("done");

	return 0;
}
