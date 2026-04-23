/*
output:
testing
done
end:
*/

#include <assert.h>
#include <stdio.h>
#include <time.h>

int
test(void)
{
	double d1, d2;
	time_t t1, t2;

	for (t1 = t2 = time(NULL); difftime(t2, t1) < 1; t2 = time(NULL))
		;

	d1 = difftime(t1, t2);
	d2 = difftime(t2, t1);
	assert(d1 + d2 < 0.00005);
}

int
main(void)
{
	puts("testing");
	test();
	puts("done");

	return 0;
}
