#include <string.h>
#include <time.h>

#include "../libc.h"
#undef localtime

struct tzone {
        char *name;
        int gmtoff;
};

#include "tz.c"

static time_t
gmtoff(char *tz)
{
	struct tzone *t;

	if (!strcmp(tz, "UTC"))
		return 0;

	for (t = tzones; t->name; t++) {
		if (!strcmp(t->name, tz))
			return t->gmtoff;
	}
	return 0;
}

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

	if (first) {
		_tzset();
		if (_tzstdoff == -1)
			_tzstdoff = gmtoff(_tzname[0]);
		if (_tzdstoff == -1)
			_tzdstoff = gmtoff(_tzname[1]);
	}
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
