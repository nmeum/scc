#include <stdlib.h>
#include <wchar.h>

#undef wcstombs

/*
 * We don't use any state in the wc* functions
 * so we don't need a mbstate_t variable
 */
size_t
wcstombs(char *restrict dest, const wchar_t *restrict src, size_t n)
{
	return wcsrtombs(dest, (void *) &src, n, NULL);
}
