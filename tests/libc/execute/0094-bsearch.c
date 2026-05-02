#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
output:
testing
done
end:
*/

static int
cmp(const void *pp1, const void *pp2)
{
	const int *p1 = pp1, *p2 = pp2;

	return *p1 - *p2;
}

static int
test(void)
{
	int *p, key, i, arr[64];

	for (i = 0; i < 64; i++)
		arr[i] = rand();

	qsort(arr, 64, sizeof(int), cmp);

	for (i = 0; i < 63; i++)
		assert(arr[i] <= arr[i+1]);

	key = arr[33];
	p = bsearch(&key, arr, 64, sizeof(int), cmp);
	assert(*p == arr[33]);
}

int
main(void)
{
	puts("testing");
	test();
	puts("done");

	return 0;
}
