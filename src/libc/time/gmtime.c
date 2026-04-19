#include <stdlib.h>
#include <time.h>

#include "../libc.h"

#undef gmtime

struct tm *
gmtime(const time_t *tim)
{
	div_t d;
	int month, year;
	time_t tday, day, t = *tim;
	static struct tm tm;

	day = t / SECDAY;
	tday = t % SECDAY;
	if (tday < 0) {
		tday += SECDAY;
		day--;
	}

	d = div(tday, 60);
	tm.tm_sec = d.rem;

	d = div(d.quot, 60);
	tm.tm_min = d.rem;

	tm.tm_hour = d.quot;

	/* 1/1/1970 was Thursday */
	tm.tm_wday = (day + THU) % 7;

	year = EPOCH;
	if (day >= 0) {
		while (day >= _daysyear(year))
			day -= _daysyear(year++);
	} else {
		while (day < 0)
			day += _daysyear(--year);
	}

	tm.tm_year = year - 1900;
	tm.tm_yday = day;

	_daysmon[FEB] = FEBDAYS(year);
	for (month = JAN; day >= _daysmon[month]; month++)
		day -= _daysmon[month];
	tm.tm_mon = month;
	tm.tm_mday = day + 1;

	tm.tm_isdst = 0;
	tm.tm_zone = "UTC";
	tm.tm_gmtoff = 0;

	return &tm;
}
