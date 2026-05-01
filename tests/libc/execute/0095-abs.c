#include <assert.h>
#include <inttypes.h>
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
main(void)
{
	puts("testing");
	assert(abs(3) == abs(-3));
	assert(abs(-INT_MAX) == INT_MAX);

	assert(labs(3) == labs(-3));
	assert(labs(-LONG_MAX) == LONG_MAX);

	assert(llabs(3) == llabs(-3));
	assert(llabs(-LLONG_MAX) == LONG_MAX);

	assert(imaxabs(3) == imaxabs(-3));
	assert(imaxabs(-INTMAX_MAX) == INTMAX_MAX);
	puts("done");

	return 0;
}
