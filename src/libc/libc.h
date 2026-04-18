struct tm;
struct _FILE;

void *_getheap(void);
int _dtoi(char c);

#ifdef stdin
int _allocbuf(FILE *);
int _flsbuf(FILE *);
FILE *_fpopen(const char * restrict, const char *restrict,
                     FILE *restrict);
#endif

#ifdef _TIME_H

#define JAN 0
#define FEB 1
#define DEC 11

#define FEBDAYS(y) ((_daysyear(y) == 366) ? 29 : 28)
#define EPOCH 1970
#define BASEYEAR 1900
#define SECMIN 60
#define SECHOUR (60 * SECMIN)    /* 3600 */
#define SECDAY (24 * SECHOUR)   /* 86400 */

enum {
	SUN,
	MON,
	TUE,
	WED,
	THU,
	FRI,
	SAT
};

struct tzone;

/* _tzone.c variables */
extern int _daylight;
extern char *_tzname[2];
extern long _timezone, _dstzone;

extern int _daysmon[12];

void _tzset(void);
int _isdst(struct tm *);
int _daysyear(int);
int _newyear(int);
char *_gmtoff(char *);
#endif

extern unsigned _exitn;
extern void (*_flushall)(void);
extern void (*_atexithdl)(void);

#ifdef _WCHAR_H
int _validutf8(wchar_t, int *);
wint_t _fputwc(wchar_t, struct _FILE *, int *);
#endif
