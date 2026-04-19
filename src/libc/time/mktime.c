#include <limits.h>
#include <time.h>

#include "../libc.h"

#undef mktime

static int
norm(int *val, int *next, int max)
{
	int v = *val, n = *next, d;

	if (v < 0) {
		d = -v / max + 1;
		v += d * max;
		if (n > INT_MAX - d)
			return 0;
		n -= d;
	}
	if (v >= max) {
		d = v / max;
		v -= d * max;
		if (n < INT_MIN + d)
			return 0;
		n += d;
	}

	*val = v;
	*next = n;
	return 1;
}

static int
normalize(struct tm *tm)
{
	int mon, day, year, yday;

	/*
	 * Normalize sec so that it doesn't over/underflow min
	 * Normalize min so that it doesn't over/underflow hour
	 * Normalize hour so that it doesn't over/underflow mday
	 * Normalize month so that it doesn't over/underflow year
	 */
	if (!norm(&tm->tm_sec, &tm->tm_min, 60)
	|| !norm(&tm->tm_min, &tm->tm_hour, 60)
	|| !norm(&tm->tm_hour, &tm->tm_mday, 24)
	|| !norm(&tm->tm_mon, &tm->tm_year, 12))
		return 0;

	day = tm->tm_mday;
	yday = 0;
	year = BASEYEAR + tm->tm_year;

	_daysmon[FEB] = FEBDAYS(year);

	/*
	 * Normalize mday so that it doesn't over/underflow month
	 * Normalize month so that it doesn't over/underflow year
	 */
	for (mon = tm->tm_mon; day < 1; --mon) {
		if (mon == JAN) {
			if (year == INT_MIN)
				return 0;
			year--;
			_daysmon[FEB] = FEBDAYS(year);
			mon = DEC+1;
		}
		day += _daysmon[mon-1];
	}

	for (; day > _daysmon[mon]; ++mon) {
		day -= _daysmon[mon];
		if (mon == DEC) {
			if (year == INT_MAX)
				return 0;
			year++;
			_daysmon[FEB] = FEBDAYS(year);
			mon = JAN-1;
		}
	}

	if (year < INT_MIN + BASEYEAR)
		return 0;
	year -= BASEYEAR;

	if (year > _MAXYEAR || year < _MINYEAR)
		return 0;

	for (int i = 0; i < mon; ++i)
		yday += _daysmon[i];

	tm->tm_mon = mon;
	tm->tm_year = year;
	tm->tm_mday = day;
	tm->tm_yday = yday + day - 1;
	tm->tm_wday = (_newyear(tm->tm_year) + tm->tm_yday) % 7;

	return 1;
}

time_t
mktime(struct tm *tm)
{
	time_t t;
	int i, year;
	struct tm *aux;

	if (!normalize(tm))
		return -1;

	t = 0;
	year = tm->tm_year + BASEYEAR;

	i = EPOCH;
	if (year >= EPOCH) {
		while (i < year)
			t += _daysyear(i++) * SECDAY;
	} else {
		while (i > year)
			t -= _daysyear(--i) * SECDAY;
	}

	for (i = 0; i < tm->tm_mon; ++i)
		t += _daysmon[i] * SECDAY;

	t += tm->tm_sec;
	t += tm->tm_min * SECMIN;
	t += tm->tm_hour * SECHOUR;
	t += (tm->tm_mday-1) * SECDAY;

	aux = localtime(&t);

	if (tm->tm_isdst == -1)
		tm->tm_isdst = aux->tm_isdst;

	if (tm->tm_isdst == 1) {
		tm->tm_zone = _tzname[1];
		tm->tm_gmtoff = _dstzone;
	} else {
		tm->tm_zone = _tzname[0];
		tm->tm_gmtoff = _timezone;
	}
	t += tm->tm_gmtoff;

	return t;
}
