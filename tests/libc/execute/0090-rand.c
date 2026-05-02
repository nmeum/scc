#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
output:
testing
test1
test2
done
end:
*/

#define NR_BINS 64
#define NR_DOTS 16000
#define CRITLVL 82.53

static void
test1(void)
{
	int max, min, i, n;
	float chi, d;
	static int bins[NR_BINS];

	puts("test1");
	for (i = 0; i < NR_DOTS; ++i) {
		n = rand();
		assert(n >= 0 && n <= RAND_MAX);
		bins[n & NR_BINS-1]++;
	}

	chi = 0;
	for (i = 0; i < NR_BINS; ++i) {
		d = bins[i] - (float) NR_DOTS / NR_BINS;
		d *= d;
		d /= (float) NR_DOTS / NR_BINS;
		chi += d;
	}

	assert(chi <= CRITLVL);
}

#undef NR_DOTS

#define NR_SEEDS 10
#define NR_DOTS  32

static void
test2(void)
{
	int i, j, dots[NR_SEEDS][NR_DOTS];
	unsigned seeds[NR_SEEDS];

	puts("test2");
	for (i = 0; i < NR_SEEDS; i++)
		seeds[i] = rand();

	for (i = 0; i < NR_SEEDS; i++) {
		srand(seeds[i]);

		for (j = 0; j < NR_DOTS; ++j)
			dots[i][j] = rand();
	}

	for (i = 0; i < NR_SEEDS; i++) {
		srand(seeds[i]);

		for (j = 0; j < NR_DOTS; ++j)
			assert(dots[i][j] == rand());
	}
}

int
main(void)
{
	puts("testing");
	test1();
	test2();
	puts("done");

	return 0;
}
