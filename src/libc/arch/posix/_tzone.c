#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../libc.h"

#define TOKENSIZ 10

enum {
	EOS,
	NUM,
	STR,
};

enum {
	GREGORIAN,
	JULIAN,
};

int _daylight;
char *_tzname[2];
long _timezone, _dstzone;

static char st[TOKENSIZ], ds[TOKENSIZ], tokstr[TOKENSIZ];
static int tok;

static int start, end;
static int julian;

static int
next(char *str)
{
	int n, t;
	static char *s;

	if (str)
		s = str;

	switch (*s) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		n = strspn(s, "0123456789");
		t = NUM;
		break;
	case '+':
	case '-':
	case ':':
	case ',':
		n = 1;
		t = *s;
		break;
	case '\0':
		n = 0;
		t = EOS;
		break;
	default:
		n = strcspn(s, "+-0123456789");
		t = STR;
		break;
	}

	if (n >= TOKENSIZ-1)
		return -1;
	memcpy(tokstr, s, n);
	tokstr[n] = '\0';
	s += n;

	return tok = t;
}

static int
accept(int c)
{
	if (tok != c)
		return 0;
	return next(NULL);
}

static int
num(int max)
{
	int n;

	if (tok == EOS)
		return 0;
	if (tok != NUM)
		return -1;
	n = atoi(tokstr);
	if (n < 0 || n > max)
		return -1;
	return n;
}

static long
offset(void)
{
	int sign = 1;
	int n;
	long off;

	if (tok == EOS)
		return -1;

	switch (tok) {
	case '+':
		sign = -1;
	case '-':
		next(NULL);
		break;
	default:
		return -1;
	}

	if ((n = num(24)) < 0)
		return -1;
	off = n * SECHOUR;
	next(NULL);
	if (tok == EOS)
		goto ret;

	if (!accept(':'))
		return -1;
	if ((n = num(60)) < 0)
		return -1;
	off += n * SECMIN;
	next(NULL);
	if (tok == EOS)
		goto ret;

	if (!accept(':'))
		return -1;
	if ((n = num(60)) < 0)
		return -1;
	off += n;
	next(NULL);

 ret:
	return sign * off;
}

static int
std(void)
{
	long off;

	if (tok != STR)
		return 0;
	strcpy(st, tokstr);
	next(NULL);

	if ((off = offset()) == -1)
		return 0;
	_timezone = off;

	return 1;
}

static int
dst(void)
{
	long off;

	if (tok != STR)
		return 0;
	strcpy(ds, tokstr);
	next(NULL);

	if ((off = offset()) == -1)
		_dstzone = _timezone + SECHOUR;
	else
		_dstzone = off;

	return _daylight = 1;
}

static int
yday(void)
{
	int type, n;

	if (tok == STR && !strcmp(tokstr, "J"))
		type = JULIAN;
	else if (tok == NUM)
		type = GREGORIAN;
	else
		return -1;

	switch (type) {
	case JULIAN:
		next(NULL);
		n = num(365);
		next(NULL);
		if (n == 0)
			return -1;
		julian = 1;
		break;
	case GREGORIAN:
		n = num(365);
		next(NULL);
		break;
	}

	return n;
}

static int
rule(void)
{
	if (tok == EOS)
		return 0;
	if (!accept(','))
		return 0;
	if ((start = yday()) == -1)
		return 0;
	if (!accept(','))
		return 0;
	if ((end = yday()) == -1)
		return 0;
}

void
_tzset(void)
{
	static char *tz;
	char *s = getenv("TZ");

	if (s && tz && strcmp(s, tz) == 0)
		return;
	tz = s;

	_daylight = 0;
	_tzname[1] = _tzname[0] = "UTC";
	_timezone = _dstzone = -1;

	start = end = -1;
	julian = 0;

	if (!tz)
		goto adjust;
	next(tz);

	if (!std())
		goto adjust;
	if (!dst())
		goto adjust;
	if (!rule())
		goto adjust;

adjust:
	if (!_daylight)
		_tzname[1] = _tzname[0];
	if (_timezone == -1)
		_timezone = _gmtoff(_tzname[0]);
	if (_dstzone == -1)
		_dstzone = _gmtoff(_tzname[1]);
}

int
_isdst(struct tm *tm)
{
	int yday;

	yday = tm->tm_yday;

	if (julian && yday+1 < 60 || FEBDAYS(tm->tm_year) < 29)
		yday++;
	if (yday >= start && yday <= end && tm->tm_hour >= 2)
		return 1;
	return 0;
}
