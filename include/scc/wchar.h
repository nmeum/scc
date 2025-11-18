#ifndef _WCHAR_H
#define _WCHAR_H

#define _NEED_NULL
#define _NEED_SIZET
#define _NEED_WCHART
#define _NEED_WEOF
#define _NEED_WCHARLIM
#define _NEED_WINT
#define _NEED_VA_LIST
#include <arch/cdefs.h>
#include <sys/cdefs.h>

typedef struct {
	unsigned char oc;
	unsigned char sh;
	wchar_t wc;
} mbstate_t;

struct tm;
struct _FILE;

int vswscanf(const wchar_t *restrict, const wchar_t *restrict, __va_list);
int vwprintf(const wchar_t *restrict, __va_list);
int vwscanf(const wchar_t *restrict, __va_list);

int fwprintf(struct _FILE *restrict, const wchar_t *restrict, ...);
int fwscanf(struct _FILE *restrict, const wchar_t *restrict, ...);

int vfwprintf(struct _FILE *restrict, const wchar_t *restrict, __va_list);
int vfwscanf(struct _FILE *restrict, const wchar_t *restrict, __va_list);
int vswprintf(wchar_t *restrict, size_t, const wchar_t *restrict, __va_list);

wint_t fgetwc(struct _FILE *);
wint_t fputwc(wchar_t, struct _FILE *);
wint_t getwc(struct _FILE *);
wint_t putwc(wchar_t, struct _FILE *);
wint_t getwchar(void);
wint_t putwchar(wchar_t);
wint_t ungetwc(wint_t, struct _FILE *);

int fwide(struct _FILE *, int);
wchar_t *fgetws(wchar_t *restrict, int, struct _FILE *restrict);
int fputws(const wchar_t *restrict, struct _FILE *restrict);

int swprintf(wchar_t *restrict, size_t, const wchar_t *restrict, ...);
int swscanf(const wchar_t *restrict, const wchar_t *restrict, ...);
int wprintf(const wchar_t *restrict, ...);
int wscanf(const wchar_t *restrict, ...);

double wcstod(const wchar_t *restrict, wchar_t **restrict);
float wcstof(const wchar_t *restrict, wchar_t **restrict);
long double wcstold(const wchar_t *restrict, wchar_t **restrict);

long int wcstol(const wchar_t *restrict, wchar_t **restrict, int);
long long int wcstoll(const wchar_t *restrict, wchar_t **restrict, int);
unsigned long int wcstoul(const wchar_t *restrict, wchar_t **restrict, int);
unsigned long long int wcstoull(const wchar_t *restrict, wchar_t **restrict, int);

wchar_t *wcscpy(wchar_t *restrict, const wchar_t *restrict);
wchar_t *wcsncpy(wchar_t *restrict, const wchar_t *restrict, size_t);

wchar_t *wmemcpy(wchar_t *restrict, const wchar_t *restrict, size_t);
wchar_t *wmemmove(wchar_t *, const wchar_t *, size_t);
wchar_t *wmemset(wchar_t *, wchar_t, size_t);
wchar_t *wmemchr(const wchar_t *, wchar_t, size_t);
int wmemcmp(const wchar_t *, const wchar_t *, size_t);

size_t wcslen(const wchar_t *);
int wcscmp(const wchar_t *, const wchar_t *);
wchar_t *wcscat(wchar_t *restrict, const wchar_t *restrict);
wchar_t *wcsncat(wchar_t *restrict, const wchar_t *restrict, size_t);
int wcscoll(const wchar_t *, const wchar_t *);
int wcsncmp(const wchar_t *, const wchar_t *, size_t);
size_t wcsxfrm(wchar_t *restrict, const wchar_t *restrict, size_t);
wchar_t *wcschr(const wchar_t *, wchar_t);
size_t wcscspn(const wchar_t *, const wchar_t *);
wchar_t *wcspbrk(const wchar_t *, const wchar_t *);
wchar_t *wcsrchr(const wchar_t *, wchar_t);
size_t wcsspn(const wchar_t *, const wchar_t *);
wchar_t *wcsstr(const wchar_t *, const wchar_t *);
wchar_t *wcstok(wchar_t *restrict, const wchar_t *restrict, wchar_t **restrict);

size_t wcsftime(wchar_t *restrict, size_t, const wchar_t *restrict, const struct tm *restrict);
wint_t btowc(int);
int wctob(wint_t);

int mbsinit(const mbstate_t *);
size_t mbrlen(const char *restrict, size_t, mbstate_t *restrict);
size_t mbrtowc(wchar_t *restrict, const char *restrict, size_t, mbstate_t *restrict);
size_t wcrtomb(char *restrict, wchar_t, mbstate_t *restrict);
size_t mbsrtowcs(wchar_t *restrict, const char **restrict, size_t, mbstate_t *restrict);
size_t wcsrtombs(char *restrict, const wchar_t **restrict, size_t, mbstate_t *restrict);
int wcwidth(wchar_t);

#define putwc(wc, fp) fputwc(wc, fp)
#define getwc(fp)     fgetwc(fp)

#endif
