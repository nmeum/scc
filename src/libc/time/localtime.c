#include <string.h>
#include <time.h>

#include "../libc.h"
#undef localtime

struct tm *
localtime(const time_t *timep)
{
	time_t t;
	int dst;
	long off;
	char *name;
	struct tm *tm;

	t = *timep;
	tm = gmtime(&t);
	_tzset();

	if (_daylight && _isdst(tm)) {
		dst = 1;
		off = _dstzone;
		name = _tzname[1];
	} else {
		dst = 0;
		off = _timezone;
		name = _tzname[0];
	}

	t += off;
	tm = gmtime(&t);
	tm->tm_zone = name;
	tm->tm_isdst = dst;
	tm->tm_gmtoff = off;

	return tm;
}
