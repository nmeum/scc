#ifndef _STDLIB_H
#define _STDLIB_H

#define _NEED_NULL
#define _NEED_SIZET
#define _NEED_WCHART
#include <sys/cdefs.h>
#include <sys/stdlib.h>
#include <arch/cdefs.h>
#include <arch/stdlib.h>

#define _ATEXIT_MAX 32
#define MB_CUR_MAX 4

#define RAND_MAX 32767

typedef struct {
	int quot, rem;
} div_t;

typedef struct {
	long quot, rem;
} ldiv_t;

typedef struct {
	long long quot, rem;
} lldiv_t;

double atof(const char *);
int atoi(const char *);
long int atol(const char *);
long long int atoll(const char *);
double strtod(const char *restrict, char **restrict);
float strtof(const char *restrict, char **restrict);
long double strtold(const char *restrict, char **restrict);
long int strtol(const char *restrict, char **restrict, int);
long long int strtoll(const char *restrict, char **restrict, int);
unsigned long int strtoul(const char *restrict, char **restrict, int);
unsigned long long int strtoull(const char *restrict, char **restrict,
                                       int);
int rand(void);
void srand(unsigned int);
void *calloc(size_t, size_t);
void free(void *);
void *malloc(size_t);
void *realloc(void *, size_t);
void abort(void);
int atexit(void (*)(void));
void exit(int);
void _Exit(int);
char *getenv(const char *);
int system(const char *);
void *bsearch(const void *, const void *, size_t, size_t,
                     int (*)(const void *, const void *));
void qsort(void *, size_t, size_t, int (*)(const void *, const void *));
int abs(int);
long int labs(long int);
long long int llabs(long long int);
div_t div(int, int);
ldiv_t ldiv(long int, long int);
lldiv_t lldiv(long long int, long long int);

int mblen(const char *, size_t);
int mbtowc(wchar_t *restrict, const char *restrict, size_t);
int wctomb(char *, wchar_t);
size_t mbstowcs(wchar_t *restrict, const char *restrict, size_t);
size_t wcstombs(char *restrict, const wchar_t *restrict, size_t);

#endif
