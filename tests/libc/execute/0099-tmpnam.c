#include <assert.h>
#include <stdio.h>
#include <string.h>

/*
output:
testing
done
end:
*/


int
test(void)
{
	int j, i, max;
	char buf[32][L_tmpnam];

	assert(TMP_MAX >= 25);

	assert(tmpnam(NULL));

        max = TMP_MAX - 1;
        if (max > FOPEN_MAX - 3)
                max = FOPEN_MAX - 3;
        if (max > 32)
                max = 32;

	for (i = 0; i < max; ++i) {
		assert(tmpnam(buf[i]));
		for (j = 0; j < i; j++)
			assert(strcmp(buf[i], buf[j]) != 0);
	}

	return 0;
}

int
main(void)
{
	puts("testing");
	test();
	puts("done");

	return 0;
}
