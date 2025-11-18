#ifndef _TIME_H
#define _TIME_H

#define _NEED_SIZET
#define _NEED_NULL
#include <sys/cdefs.h>
#include <arch/cdefs.h>
#include <arch/time.h>

struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;

	/* fields used internally */

	char *tm_zone;
	long tm_gmtoff;
};

clock_t clock(void);
double difftime(time_t, time_t);
time_t mktime(struct tm *);
time_t time(time_t *);
char *asctime(const struct tm *);
char *ctime(const time_t *);
struct tm *gmtime(const time_t *);
struct tm *localtime(const time_t *);
size_t strftime(char *restrict, size_t, const char *restrict,
                       const struct tm *restrict);

#endif
