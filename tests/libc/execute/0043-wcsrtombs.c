#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

/*
output:
testing
testing wcsrtombs1
testing wcsrtombs2
testing wcstombs
done
end:
*/

#define NELEM(x) (sizeof(x)/sizeof(x[0]))

static char str[20];
static wchar_t wcs[20];

static struct wcstests {
	char *s;
	char *sexp;

	wchar_t *wcs;
	wchar_t *wcsexp;

	size_t n;
	int r;
	int syserr;
	int mbstate;
} tests [] = {
        /* s      sexp  wcs                     wcsexp   n  r  syserr  mbstate */
	{str,     "\0", (wchar_t[]) {0},        NULL,    1, 0,      0,       1},
	{str,     "\0", (wchar_t[]) {0},        wcs,     0, 0,      0,       1},
	{NULL,    NULL, (wchar_t[]) {0},        NULL,    1, 0,      0,       1},
	{NULL,    NULL, (wchar_t[]) {0},        NULL,    0, 0,      0,       1},

	{str,   "\x31", (wchar_t[]) {0x31, 0},  NULL,    2, 1,      0,       1},
	{str,   "\x31", (wchar_t[]) {0x31, 0},  wcs+1,   1, 1,      0,       1},
	{NULL,    NULL, (wchar_t[]) {0x31, 0},  NULL,    1, 1,      0,       1},
	{NULL,    NULL, (wchar_t[]) {0x31, 0},  NULL,    0, 1,      0,       1},

	{str,
	 "\x21\xc2\xa1\xe2\x80\x94\xf0\x9f\x92\xa9",
	 (wchar_t[]) {0x21,0xa1,0x2014,0x1f4A9, 0},NULL, 20,10,     0,       1}, 

	{str,   "\x31", (wchar_t[]) {0x31, 0xD800}, wcs, 20,-1,  EILSEQ,     0},
};

static void
tests_wcsrtombs(void)
{
	size_t r;
	wchar_t *wc;
	mbstate_t st;
	struct wcstests *tp;

	puts("testing wcsrtombs1");
	for (tp = tests; tp < &tests[NELEM(tests)]; ++tp) {
		errno = 0;
		wc = wcscpy(wcs, tp->wcs);
		memset(str, -1, sizeof(str));

		r = wcsrtombs(tp->s, &wc, tp->n, NULL);
		assert(tp->r == r);
		assert(tp->syserr == errno);
		if (tp->r >= 0) {
			assert(wc == tp->wcsexp);
			if (tp->s)
				assert(!strncmp(tp->sexp, tp->s, r));
		}
	}

	puts("testing wcsrtombs2");
	for (tp = tests; tp < &tests[NELEM(tests)]; ++tp) {
		errno = 0;
		wc = wcscpy(wcs, tp->wcs);
		memset(str, -1, sizeof(str));
		memset(&st, 0, sizeof(st));

		r = wcsrtombs(tp->s, &wc, tp->n, &st);
		assert(tp->r == r);
		assert(tp->syserr == errno);
		if (tp->r >= 0) {
			assert(wc == tp->wcsexp);
			if (tp->s)
				assert(!strncmp(tp->sexp, tp->s, r));
			assert(mbsinit(&st) != 0 == tp->mbstate);
		}
	}

}

static void
tests_wcstombs(void)
{
	size_t r;
	wchar_t *wc;
	struct wcstests *tp;

	puts("testing wcstombs");
	for (tp = tests; tp < &tests[NELEM(tests)]; ++tp) {
		errno = 0;
		wc = wcscpy(wcs, tp->wcs);
		memset(str, -1, sizeof(str));

		r = wcstombs(tp->s, wc, tp->n);
		assert(tp->r == r);
		if (tp->r >= 0 && tp->s)
			assert(!strncmp(tp->sexp, tp->s, r));
	}
}

int
main(void)
{
	puts("testing");
	tests_wcsrtombs();
	tests_wcstombs();
	puts("done");
	return 0;
}
