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
	int n;
	char buf[64];

	n = atoi("abc");
	assert(n == 0);

	n = atoi(" abc");
	assert(n == 0);

	n = atoi("1234 ");
	assert(n == 1234);

	n = atoi(" 1234 0");
	assert(n == 1234);

	n = atoi("+");
	assert(n == 0);

	n = atoi(" +1");
	assert(n == 1);

	n = atoi("+ 1");
	assert(n == 0);

	n = atoi(" -1");
	assert(n == -1);

	n = atoi("- 1");
	assert(n == 0);

	sprintf(buf, "%d", INT_MAX);
	n = atoi(buf);
	assert(n == INT_MAX);

	sprintf(buf, "%d", INT_MIN);
	n = atoi(buf);
	assert(n == INT_MIN);
}

int
main()
{
	puts("testing");
	test();
	puts("done");

	return 0;
}
