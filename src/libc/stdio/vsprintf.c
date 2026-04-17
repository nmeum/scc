#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#undef vsprintf

int
vsprintf(char *restrict s, const char *restrict fmt, va_list va)
{
	/*
	 * we used to use SIZE_MAX here, but that is just
	 * wrong because we build a rp pointer that in that
	 * case it is just wp - 1 by definition. As it
	 * is impossible to span an object further than
	 * the end of the memory space we can use the number
	 * of bytes until the end of the address space.
	 */
	return vsnprintf(s, (char *)-1 - s, fmt, va);
}
