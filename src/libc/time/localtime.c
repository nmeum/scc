#include <string.h>
#include <time.h>

#include "../libc.h"
#undef localtime

struct tm *
localtime(const time_t *timep)
{
	int dst;
	time_t t;
	long off;
	char *name;
	struct tm *tm;

	_tzset();
	t = *timep - _timezone;
	if (_isdst(gmtime(&t))) {
		dst = 1;
		off = _dstzone;
		name = _tzname[1];
	} else {
		dst = 0;
		off = _timezone;
		name = _tzname[0];
	}

	t = *timep - off;
	tm = gmtime(&t);
	tm->tm_zone = name;
	tm->tm_isdst = dst;
	tm->tm_gmtoff = off;

	return tm;
}
