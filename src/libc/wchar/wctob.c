#include <stdio.h>
#include <wchar.h>

#undef wctob

int
wctob(wint_t wc)
{
	unsigned long w = wc;

	if (wc == WEOF || w > 128)
		return EOF;
	return wc;
}
