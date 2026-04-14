#include <time.h>

#include "../../libc.h"

time_t
_systime(struct tm *tm)
{
	int i;
	time_t t = 0;
	int year = tm->tm_year + MINYEAR;

	for (i = EPOCH; i < year; ++i)
		t += _daysyear(i) * SECDAY;
	for (i = 0; i < tm->tm_mon; ++i)
		t += _daysmon[i] * SECDAY;

	t += tm->tm_sec;
	t += tm->tm_min * SECMIN;
	t += tm->tm_hour * SECHOUR;
	t += (tm->tm_mday-1) * SECDAY;
	return t;
}
