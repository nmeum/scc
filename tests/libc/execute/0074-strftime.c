/*
output:
testing
test1:
	test 0
		n=6:Friday
	test 1
		n=7:January
	test 2
		n=2:20
	test 3
		n=8:01/01/21
	test 4
		n=10:2021-01-01
	test 5
		n=4:2020
	test 6
		n=2:10
	test 7
		n=2:10
	test 8
		n=2:30
	test 9
		n=5:10:30
	test 10
		n=2:59
	test 11
		n=8:14:30:59
	test 12
		n=2:00
	test 13
		n=2:53
	test 14
		n=2:00
	test 15
		n=8:14:30:59
	test 16
		n=4:2021
	test 17
		n=4:2021
	test 18
		n=3:UTC
	test 19
		n=3:Fri
	test 20
		n=3:Jan
	test 21
		n=24:Fri Jan  1 10:30:59 2021
	test 22
		n=2:01
	test 23
		n=2: 1
	test 24
		n=2:20
	test 25
		n=3:Jan
	test 26
		n=3:001
	test 27
		n=2:01
	test 28
		n=1:

	test 29
		n=2:AM
	test 30
		n=2:PM
	test 31
		n=1:%
	test 32
		n=11:02:30:59 PM
	test 33
		n=1:	
	test 34
		n=1:5
	test 35
		n=1:5
	test 36
		n=8:01/01/21
	test 37
		n=2:21
	test 38
		n=5:+0000
	test 39
		n=7:49 1997
	test 40
		n=7:53 1998
test2:
test3:
test4:
test5:
test6:
test7:
test8:
test9:
test10:
test11:
test12:
test13:
test14:
test15:
test16:
test17:
test18:
test18:
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
	char *fmt;
} tests[] = {
	//sec, min,hour,mday,mon,year,wday,yday,isdst, fmt
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%A"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%B"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%C"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%D"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%F"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%G"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%H"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%I"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%M"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%R"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%S"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%T"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%U"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%V"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%W"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%X"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%Y"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%Y"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%Z"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%a"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%b"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%c"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%d"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%e"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%g"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%h"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%j"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%m"},
	{{0},                                          "%n"},
	{{ 59,  30,  10,   1,  0, 121,   5,   0},      "%p"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%p"},
	{{0},                                          "%%"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%r"},
	{{0},                                          "%t"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%u"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%w"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%x"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%y"},
	{{ 59,  30,  14,   1,  0, 121,   5,   0},      "%z"},
	{{ 59,  30,  10,   1, 11,  97,   2, 363},      "%V %G"},
	{{ 59,  30,  10,   2,  0,  99,   6,   1},      "%V %G"},
};

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
 * fallback to putenv this will work in the systems we are
 * interested on
 */
char *
getenv(const char *name)
{
	if (strcmp(name, "TZ") != 0)
		return NULL;
	return "UTC";
}
#endif

void
test1(void)
{
	int n;
	char buf[70];
	struct test *tp;

	puts("test1:");
	for (tp = tests; tp < &tests[NELEM(tests)]; ++tp) {
		printf("\ttest %d\n", (int) (tp - tests));
		mktime(&tp->tm);
		n = strftime(buf, sizeof(buf), tp->fmt, &tp->tm);
		printf("\t\tn=%d:%s\n", n, buf);
	}
}

void
test2(void)
{
	struct tm tm;
	char s1[32], s2[32];
	size_t n1, n2;

	puts("test2:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 10;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 32, "%c", &tm);
	n2 = strftime(s2, 32, "%Ec", &tm);

	assert(n1 == 24 && strcmp(s1, "Fri Jan  1 10:30:59 2021") == 0);
	assert(n2 == 24 && strcmp(s2, "Fri Jan  1 10:30:59 2021") == 0);
}

void
test3(void)
{
	struct tm tm;
	char s1[8], s2[8];
	size_t n1, n2;

	puts("test3:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 10;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 8, "%d", &tm);
	n2 = strftime(s2, 8, "%Od", &tm);

	assert(n1 == 2 && strcmp(s1, "01") == 0);
	assert(n2 == 2 && strcmp(s2, "01") == 0);
}

void
test4(void)
{
	struct tm tm;
	char s1[8], s2[8];
	size_t n1, n2;

	puts("test4:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 10;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 8, "%e", &tm);
	n2 = strftime(s2, 8, "%Oe", &tm);

	assert(n1 == 2 && strcmp(s1, " 1") == 0);
	assert(n2 == 2 && strcmp(s2, " 1") == 0);
}

void
test5(void)
{
	struct tm tm;
	char s1[8], s2[8];
	size_t n1, n2;

	puts("test5:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 14;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 8, "%m", &tm);
	n2 = strftime(s2, 8, "%Om", &tm);

	assert(n1 == 2 && strcmp(s1, "01") == 0);
	assert(n2 == 2 && strcmp(s2, "01") == 0);
}

void
test6(void)
{
	struct tm tm;
	char s1[8], s2[8];
	size_t n1, n2;

	puts("test6:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 14;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 8, "%u", &tm);
	n2 = strftime(s2, 8, "%Ou", &tm);

	assert(n1 == 1 && strcmp(s1, "5") == 0);
	assert(n2 == 1 && strcmp(s2, "5") == 0);
}

void
test7(void)
{
	struct tm tm;
	char s1[8], s2[8];
	size_t n1, n2;

	puts("test7:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 14;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 8, "%w", &tm);
	n2 = strftime(s2, 8, "%Ow", &tm);

	assert(n1 == 1 && strcmp(s1, "5") == 0);
	assert(n2 == 1 && strcmp(s2, "5") == 0);
}

void
test8(void)
{
	struct tm tm;
	char s1[16], s2[16];
	size_t n1, n2;

	puts("test8:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 14;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 16, "%x", &tm);
	n2 = strftime(s2, 16, "%Ex", &tm);

	assert(n1 == 8 && strcmp(s1, "01/01/21") == 0);
	assert(n2 == 8 && strcmp(s2, "01/01/21") == 0);
}

void
test9(void)
{
	struct tm tm;
	char s1[8], s2[8], s3[8];
	size_t n1, n2, n3;

	puts("test9:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 14;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 8, "%y", &tm);
	n2 = strftime(s2, 8, "%Ey", &tm);
	n3 = strftime(s3, 8, "%Oy", &tm);

	assert(n1 == 2 && strcmp(s1, "21") == 0);
	assert(n2 == 2 && strcmp(s2, "21") == 0);
	assert(n3 == 2 && strcmp(s3, "21") == 0);
}

void
test10(void)
{
	struct tm tm;
	char s1[8], s2[8];
	size_t n1, n2;

	puts("test10:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 10;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 8, "%C", &tm);
	n2 = strftime(s2, 8, "%EC", &tm);

	assert(n1 == 2 && strcmp(s1, "20") == 0);
	assert(n2 == 2 && strcmp(s2, "20") == 0);
}

void
test11(void)
{
	struct tm tm;
	char s1[8], s2[8];
	size_t n1, n2;

	puts("test11:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 14;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 8, "%H", &tm);
	n2 = strftime(s2, 8, "%OH", &tm);

	assert(n1 == 2 && strcmp(s1, "14") == 0);
	assert(n2 == 2 && strcmp(s2, "14") == 0);
}

void
test12(void)
{
	struct tm tm;
	char s1[8], s2[8];
	size_t n1, n2;

	puts("test12:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 14;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(&s1[0], 8, "%I", &tm);
	n2 = strftime(&s2[0], 8, "%OI", &tm);

	assert(n1 == 2 && strcmp(s1, "02") == 0);
	assert(n2 == 2 && strcmp(s2, "02") == 0);
}

void
test13(void)
{
	struct tm tm;
	char s1[8], s2[8];
	size_t n1, n2;

	puts("test13:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 14;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 8, "%M", &tm);
	n2 = strftime(s2, 8, "%OM", &tm);

	assert(n1 == 2 && strcmp(s1, "30") == 0);
	assert(n2 == 2 && strcmp(s2, "30") == 0);
}

void
test14(void)
{
	struct tm tm;
	char s1[8], s2[8];
	size_t n1, n2;

	puts("test14:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 14;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 8, "%S", &tm);
	n2 = strftime(s2, 8, "%OS", &tm);

	assert(n1 == 2 && strcmp(s1, "59") == 0);
	assert(n2 == 2 && strcmp(s2, "59") == 0);
}

void
test15(void)
{
	struct tm tm;
	char s1[8], s2[8];
	size_t n1, n2;

	puts("test15:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 14;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 8, "%U", &tm);
	n2 = strftime(s2, 8, "%OU", &tm);

	assert(n1 == 2 && strcmp(s1, "00") == 0);
	assert(n2 == 2 && strcmp(s2, "00") == 0);
}

void
test16(void)
{
	struct tm tm;
	char s1[8], s2[8];
	size_t n1, n2;

	puts("test16:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 14;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 8, "%V", &tm);
	n2 = strftime(s2, 8, "%OV", &tm);

	assert(n1 == 2 && strcmp(s1, "53") == 0);
	assert(n2 == 2 && strcmp(s2, "53") == 0);
}

void
test17(void)
{
	struct tm tm;
	char s1[8], s2[8];
	size_t n1, n2;

	puts("test17:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 14;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 8, "%W", &tm);
	n2 = strftime(s2, 8, "%OW", &tm);

	assert(n1 == 2 && strcmp(s1, "00") == 0);
	assert(n2 == 2 && strcmp(s2, "00") == 0);

}

void
test18(void)
{
	struct tm tm;
	char s1[16], s2[16];
	size_t n1, n2;

	puts("test18:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 14;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(&s1[0], 16, "%X", &tm);
	n2 = strftime(&s2[0], 16, "%EX", &tm);

	assert(n1 == 8 && strcmp(s1, "14:30:59") == 0);
	assert(n2 == 8 && strcmp(s2, "14:30:59") == 0);
}

void
test19(void)
{
	struct tm tm;
	char s1[8], s2[8];
	size_t n1, n2;

	puts("test18:");
	tm.tm_sec = 59;
	tm.tm_min = 30;
	tm.tm_hour = 14;
	tm.tm_mday = 1;
	tm.tm_mon = 0;
	tm.tm_year = 121;
	tm.tm_wday = 5;
	tm.tm_yday = 0;

	n1 = strftime(s1, 8, "%Y", &tm);
	n2 = strftime(s2, 8, "%EY", &tm);

	assert(n1 == 4 && strcmp(s1, "2021") == 0);
	assert(n2 == 4 && strcmp(s2, "2021") == 0);
}

int
main(void)
{
	puts("testing");
	putenv("TZ=UTC");
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	test11();
	test12();
	test13();
	test14();
	test15();
	test16();
	test17();
	test18();
	test19();
	puts("done");

	return 0;
}
