#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/*
output:
testing
done
end:
*/

void
test(void)
{
	long n;
	char buf[64];

	n = atol("abc");
	assert(n == 0);

	n = atol(" abc");
	assert(n == 0);

	n = atol("1234 ");
	assert(n == 1234);

	n = atol(" 1234 0");
	assert(n == 1234);

	n = atol("+");
	assert(n == 0);

	n = atol(" +1");
	assert(n == 1);

	n = atol("+ 1");
	assert(n == 0);

	n = atol(" -1");
	assert(n == -1);

	n = atol("- 1");
	assert(n == 0);

	sprintf(buf, "%ld", LONG_MAX);
	n = atol(buf);
	assert(n == LONG_MAX);

	sprintf(buf, "%ld", LONG_MIN);
	n = atol(buf);
	assert(n == LONG_MIN);
}

int
main()
{
	puts("testing");
	test();
	puts("done");

	return 0;
}
