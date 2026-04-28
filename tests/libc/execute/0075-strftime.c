/*
output:
testing
done
end:
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static struct tm *tm;
static time_t t;
static char buf[256];

void
testval(const char *fmt, size_t siz, size_t expect)
{
	size_t r;

	r = strftime(buf, siz, fmt, tm);
	if (r != expect) {
		printf("test failed, fmt=%s, siz=%zu, result=%zu, expected=%zu\n",
		        fmt, siz, r, expect);
		exit(1);
	}
}

int
main(void)
{
	puts("testing");
	t = time(NULL);
	if (t == (time_t)-1)
		return 1;

	tm = gmtime(&t);
	if (tm == NULL)
		return 1;

	/* "GMT" */
	testval("%Z", sizeof(buf), 3);
	testval("%Z", 4, 3); /* fit exactly */
	testval("%Z", 3, 0); /* too small */
	testval("%Z", 2, 0); /* too small */

	testval("%Y", sizeof(buf), 4);
	testval("%Y", 5, 4); /* fit exactly */
	testval("%Y", 4, 0); /* too small */
	testval("%Y", 2, 0); /* too small */

	testval("%G", sizeof(buf), 4);
	testval("%G", 5, 4); /* fit exactly */
	testval("%G", 4, 0); /* too small */
	testval("%G", 2, 0); /* too small */

	testval("%%", sizeof(buf), 1);
	testval("%%", 2, 1); /* fit exactly */
	testval("%%", 1, 0); /* too small */
	testval("%%", 0, 0); /* too small */

	testval("%d", sizeof(buf), tm->tm_mday > 10 ? 2 : 1);
	testval("%d", tm->tm_mday > 10 ? 3 : 2, tm->tm_mday > 10 ? 2 : 1); /* fit exactly */
	testval("%d", tm->tm_mday > 10 ? 2 : 1, 0); /* too small */
	testval("%d", 0, 0); /* too small */

	testval("abc", sizeof(buf), 3);
	testval("abc", 4, 3); /* fit exactly */
	testval("abc", 3, 0); /* too small */
	testval("abc", 0, 0); /* too small */

	testval("%t", sizeof(buf), 1);
	testval("%t", 2, 1); /* fit exactly */
	testval("%t", 1, 0); /* too small */
	testval("%t", 0, 0); /* too small */

	/* "AM" or "PM" */
	testval("%p", sizeof(buf), 2);
	testval("%p", 3, 2); /* fit exactly */
	testval("%p", 2, 0); /* too small */
	testval("%p", 0, 0); /* too small */

	testval("", sizeof(buf), 0);
	testval("", 1, 0); /* fit exactly */
	testval("", 0, 0); /* too small */

	/* weekday */
	testval("%w", sizeof(buf), 1);
	testval("%w", 2, 1); /* fit exactly */
	testval("%w", 1, 0); /* too small */
	testval("%w", 0, 0); /* too small */

	/* same as "%Y-%m-%d", recursive */
	testval("%F", sizeof(buf), 10);
	testval("%F", 11, 10); /* fit exactly */
	testval("%F", 10, 0); /* too small */
	testval("%F", 0, 0); /* too small */

	/* week number of the year, monday of first year, padded with '0', 0-53 */
	tm->tm_yday = 1;
	testval("%W", sizeof(buf), 2);
	testval("%W", 3, 2); /* fit exactly */
	testval("%W", 2, 0); /* too small */
	testval("%W", 0, 0); /* too small */

	/* week number of the year, padded with '0' */
	tm->tm_yday = 1; /* 1 */
	tm->tm_mon = 0; /* january */
	tm->tm_year = 122; /* 2022 */
	tm->tm_wday = 6; /* saturday */
	testval("%V", sizeof(buf), 2);
	testval("%V", 3, 2); /* fit exactly */
	testval("%V", 2, 0); /* too small */
	testval("%V", 0, 0); /* too small */

	tm->tm_wday = 10;
	testval("%w", sizeof(buf), 1);
	testval("%w", 2, 1); /* fit exactly */
	testval("%w", 1, 0); /* too small */
	testval("%w", 0, 0); /* too small */
	puts("done");

	return 0;
}
