#include <stdlib.h>
#include <wchar.h>

#undef wctomb

/*
 * We don't use any state in the wc* functions
 * so we don't need a mbstate_t variable
 */
int
wctomb(char *s, wchar_t wc)
{
	return wcrtomb(s, wc, NULL);
}
