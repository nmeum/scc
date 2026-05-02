#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/*
output:
testing
done
end:
*/


int
test(void)
{
	unsigned long n;
	char buf[64], *endp;

	errno = 0;
	n = strtoul("1024", NULL, 10);
	assert(n == 1024 && errno == 0);

	n = strtoul("1024", &endp, 10);
	assert(n == 1024 && errno == 0 && *endp == '\0');

	n = strtoul("1000", &endp, 10);
	assert(n == 1000 && errno == 0 && *endp == '\0');

	n = strtoul("1000", &endp, 8);
	assert(n == 512 && errno == 0 && *endp == '\0');

	n = strtoul("1000", &endp, 16);
	assert(n == 4096 && errno == 0 && *endp == '\0');

	n = strtoul("1000", &endp, 0);
	assert(n == 1000 && errno == 0 && *endp == '\0');

	n = strtoul("0x1000", &endp, 0);
	assert(n == 4096 && errno == 0 && *endp == '\0');

	n = strtoul("01000", &endp, 0);
	assert(n == 512 && errno == 0 && *endp == '\0');

	n = strtoul(" +1a", &endp, 0);
	assert(n == 1 && errno == 0 && *endp == 'a');

	n = strtoul(" -1a", &endp, 0);
	assert(n == -1 && errno == 0 && *endp == 'a');

	sprintf(buf, "%lu", ULONG_MAX);
	n = strtoul(buf, NULL, 10);
	assert(n == ULONG_MAX && errno == 0);

	sprintf(buf, "%ld", LONG_MIN);
	n = strtoul(buf, NULL, 10);
	assert(n == LONG_MIN && errno == 0);

	n = strtoul("9999999999999999999999999", NULL, 10);
	assert(n == ULONG_MAX && errno == ERANGE);

	errno = 0;
	n = strtoul("-999999999999999999999999", NULL, 10);
	assert(n == ULONG_MAX && errno == ERANGE);
}

int
main(void)
{
	puts("testing");
	test();
	puts("done");

	return 0;
}
