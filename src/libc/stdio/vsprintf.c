#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#undef vsprintf

int
vsprintf(char *restrict s, const char *restrict fmt, va_list va)
{
	uintptr_t addr = (uintptr_t) s;

	return vsnprintf(s, UINTPTR_MAX - addr, fmt, va);
}
