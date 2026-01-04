#include <stdio.h>
#include <wchar.h>

#undef btowc

wint_t
btowc(int ch)
{
	unsigned char c = ch;

	if (ch == EOF || c >= 128)
		return WEOF;
	return ch;
}
