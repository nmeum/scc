#include <string.h>
#include <time.h>

#include "../libc.h"
#undef localtime

struct tm *
localtime(const time_t *timep)
{
	char *name;
	struct tm *tm;
	time_t t, off;
	int yday, dst;
	static int first = 1;

	t = *timep;
	tm = gmtime(&t);
	yday = tm->tm_yday;

	if (first)
		_tzset();
	first = 0;

	off = _tzstdoff;
	name = _tzname[0];
	dst = 0;

	if (_tzjulian && yday+1 < 60 || FEBDAYS(tm->tm_year) < 29)
		yday++;

	if (yday >= _tzstart && yday <= _tzend && tm->tm_hour >= 2) {
		off = _tzdstoff;
		name = _tzname[1];
		dst = 1;
	}

	t += off;
	tm = gmtime(&t);

	tm->tm_zone = name;
	tm->tm_isdst = dst;
	tm->tm_gmtoff = off;

	return tm;
}
