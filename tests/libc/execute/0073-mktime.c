/*
output:
testing
test 0
tm_sec=59, tm_min=30, tm_hour=12, tm_mday=28, tm_mon= 0, tm_year= 121, tm_wday=4, tm_yday= 27, tm_isdst=0
Thu Jan 28 12:30:59 2021 CET
Thu Jan 28 13:30:59 2021 UTC
Thu Jan 28 12:30:59 2021 CET
Thu Jan 28 12:30:59 2021
Thu Jan 28 12:30:59 2021
done
end:
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NELEM(x) (sizeof(x)/sizeof((x)[0]))

struct test {
	struct tm tm;
	char *tz;
} tests[] = {
	//sec,min,hour,mday,mon,year,wday,yday,isdst,tz,
	{{ 59, 30,  12,  28,  0, 121,  0,   0,   0},"CET01CEST"},
};

char *faketz;

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
	return faketz;
}
#endif

int
test(void)
{
	time_t t;
	char buf[70], var[70], *tz;
	struct tm *tm;
	struct test *tp;

	for (tp = tests; tp < &tests[NELEM(tests)]; ++tp) {
		printf("test %d\n", (int) (tp - tests));
		tz = tp->tz;
		if (!tz)
			tz = "UTC";
		faketz = tz;
		sprintf(var, "TZ=%s", tz);
		putenv(var);

		t = mktime(&tp->tm);
		if (t == -1) {
			puts("failed");
			continue;
		}
		printf("tm_sec=%2d, "
		       "tm_min=%2d, "
		       "tm_hour=%2d, "
		       "tm_mday=%2d, "
		       "tm_mon=%2d, "
		       "tm_year=%4d, "
		       "tm_wday=%d, "
		       "tm_yday=%3d, "
		       "tm_isdst=%d\n",
		       tp->tm.tm_sec,
		       tp->tm.tm_min,
		       tp->tm.tm_hour,
		       tp->tm.tm_mday,
		       tp->tm.tm_mon,
		       tp->tm.tm_year,
		       tp->tm.tm_wday,
		       tp->tm.tm_yday,
		       tp->tm.tm_isdst);
		strftime(buf, sizeof(buf), "%c %Z", &tp->tm);
		puts(buf);

		tm = gmtime(&t);
		strftime(buf, sizeof(buf), "%c %Z", tm);
		puts(buf);

		tm = localtime(&t);
		strftime(buf, sizeof(buf), "%c %Z", tm);
		puts(buf);

		fputs(asctime(tm), stdout);
		fputs(ctime(&t), stdout);
	}

	return 0;
}

int
main(void)
{
#if !defined(__SCC_TZ_TIME__)
	puts("RESULT: SKIP");
	return 0;
#endif
	puts("testing");
	test();
	puts("done");
	return 0;
}
