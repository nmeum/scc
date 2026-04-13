enum {
	SUN,
	MON,
	TUE,
	WED,
	THU,
	FRI,
	SAT
};

#define JAN 0
#define FEB 1
#define DEC 11

#define FEBDAYS(y) ((_daysyear(y) == 366) ? 29 : 28)
#define EPOCH 1970
#define MINYEAR 1900
#define SECMIN 60
#define SECHOUR (60 * SECMIN)    /* 3600 */
#define SECDAY (24 * SECHOUR)   /* 86400 */

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
extern time_t _tzstdoff, _tzdstoff;
extern time_t _tzstart, _tzend;

time_t _systime(struct tm *);
#endif

void _tzset(void);
int _daysyear(int);
int _newyear(int);

extern int _tzjulian;
extern int _daysmon[12];
extern char *_tzname[2];

extern unsigned _exitn;
extern void (*_flushall)(void);
extern void (*_atexithdl)(void);

#ifdef _WCHAR_H
int _validutf8(wchar_t, int *);
wint_t _fputwc(wchar_t, struct _FILE *, int *);
#endif
