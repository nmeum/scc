#include <stdio.h>
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

static int tok;
static char tokstr[TOKENSIZ];

static int sjulian, start;
static int ejulian, end;
static long shour, ehour;

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
	case '/':
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
		n = strcspn(s, "+-0123456789,/");
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
	long off;
	int n, sign = 1;

	if (tok == EOS)
		return -1;

	switch (tok) {
	case '-':
		sign = -1;
	case '+':
		next(NULL);
		break;
	}

	if ((n = num(24)) < 0)
		return -1;
	off = n * SECHOUR;
	next(NULL);
	if (tok == EOS)
		goto ret;

	if (!accept(':'))
		goto ret;
	if ((n = num(60)) < 0)
		return -1;
	off += n * SECMIN;
	next(NULL);

	if (!accept(':'))
		goto ret;
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
	char *name;

	if ((name = _gmtoff(tokstr)) == NULL)
		return 0;

	next(NULL);
	if ((off = offset()) == -1)
		return 0;

	_tzname[0] = name;
	_timezone = off;

	return 1;
}

static int
dst(void)
{
	long off;
	char *name;

	if ((name = _gmtoff(tokstr)) == NULL)
		return 0;
	_tzname[1] = name;

	next(NULL);
	if ((off = offset()) == -1)
		_dstzone = _timezone - SECHOUR;
	else
		_dstzone = off;

	return _daylight = 1;
}

static int
yday(int *julian, long *hour)
{
	long off;
	int type, n;

	if (tok == STR && !strcmp(tokstr, "J"))
		type = JULIAN;
	else if (tok == NUM)
		type = GREGORIAN;
	else
		return -1;

	switch (type) {
	case JULIAN:
		*julian = 1;
		next(NULL);
		n = num(365);
		next(NULL);
		if (n == 0)
			return -1;
		n--;
		break;
	case GREGORIAN:
		*julian = 0;
		n = num(365);
		next(NULL);
		break;
	}
	if (accept('/')) {
		if ((off = offset()) < 0)
			return -1;
		*hour = off;
	}
	return n;
}

static int
rule(void)
{
	shour = ehour = 2 * SECHOUR;

	if (!accept(','))
		return 0;
	if ((start = yday(&sjulian, &shour)) == -1)
		return 0;
	if (!accept(','))
		return 0;
	if ((end = yday(&ejulian, &ehour)) == -1)
		return 0;
}

void
_tzset(void)
{
	static char *tz;
	static char cache[80];
	char *s = getenv("TZ");

	if (s) {
		if (tz && strcmp(s, tz) == 0)
			return;
		snprintf(cache, sizeof(cache), "%s", s);
		tz = cache;
	}

	if (!s || next(s) == EOS)
		goto error;

	start = end = -1;

	if (!std())
		goto error;
	if (tok == EOS)
		goto adjust;

	if (!dst())
		goto error;
	if (tok == EOS)
		goto adjust;

	if (!rule())
		goto error;
	if (tok != EOS)
		goto error;

adjust:
	if (!_daylight) {
		_tzname[1] = _tzname[0];
		_dstzone = _timezone;
	}

	return;

error:
	_daylight = 0;
	_tzname[1] = _tzname[0] = "UTC";
	_timezone = _dstzone = 0;
}

int
_isdst(struct tm *tm)
{
	long off;
	int day, bis, yday;

	if (!_daylight)
		return 0;

	bis = FEBDAYS(tm->tm_year) == 29;
	yday = tm->tm_yday;
	off = tm->tm_hour * SECHOUR;
	off += tm->tm_min * SECMIN;
	off += tm->tm_sec;

	day = start;
	if (sjulian && bis && day >= 59)
		day++;
	if (yday < day || yday == day && off < shour)
		return 0;

	day = end;
	if (ejulian && bis && day >= 59)
		day++;
	if (yday > day || yday == day && off > ehour)
		return 0;

	return 1;
}
