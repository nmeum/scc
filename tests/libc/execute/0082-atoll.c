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
	long long n;
	char buf[64];

	n = atoll("abc");
	assert(n == 0);

	n = atoll(" abc");
	assert(n == 0);

	n = atoll("1234 ");
	assert(n == 1234);

	n = atoll(" 1234 0");
	assert(n == 1234);

	n = atoll("+");
	assert(n == 0);

	n = atoll(" +1");
	assert(n == 1);

	n = atoll("+ 1");
	assert(n == 0);

	n = atoll(" -1");
	assert(n == -1);

	n = atoll("- 1");
	assert(n == 0);

	sprintf(buf, "%lld", LONG_MAX);
	n = atoll(buf);
	assert(n == LLONG_MAX);

	sprintf(buf, "%lld", LONG_MIN);
	n = atoll(buf);
	assert(n == LLONG_MIN);
}

int
main()
{
	puts("testing");
	test();
	puts("done");

	return 0;
}
