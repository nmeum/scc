/*
PATTERN:
0040-vararg.c:23: warning: second parameter of 'va_start' not last named argument
0040-vararg.c:27: warning: 'fmt' defined but not used
.
*/

typedef __builtin_va_list __va_list;

typedef __va_list va_list;

#define va_start(ap, last) __builtin_va_start(ap, last)
#define va_end(ap) __builtin_va_end(ap)
#define va_copy(to, from) __builtin_va_copy(to, from)
#define va_arg(to, type) __builtin_va_arg(to, type)


void
die1(int id, const char *fmt, ...)
{
        va_list ap;

        va_start(ap, id);
        va_end(ap);
}

void
die2(const char *fmt, ...)
{
        va_list ap;

        va_start(ap, fmt);
        va_end(ap);
}

int
main(void)
{
	return 0;
}
