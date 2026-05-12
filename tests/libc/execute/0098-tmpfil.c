#include <assert.h>
#include <stdio.h>
#include <string.h>

/*
output:
testing
test1
test2
done
end:
*/

static void
test1(void)
{
	char buf[80];
	FILE *fp1, *fp2;

	puts("test1");
	fp1 = tmpfile();
	assert(fp1);
	fp2 = tmpfile();
	assert(fp2);

	fputs("This is the first\n", fp1);
	fputs("This is the second\n", fp2);
	fflush(fp1);
	fflush(fp2);

	rewind(fp1);
	rewind(fp2);

	fgets(buf, sizeof(buf), fp1);
	assert(strcmp(buf, "This is the first\n") == 0);

	fgets(buf, sizeof(buf), fp2);
	assert(strcmp(buf, "This is the second\n") == 0);

	assert(fclose(fp1) == 0);
	assert(fclose(fp2) == 0);
}

static void
test2(void)
{
	int i, max;
	FILE *fp;
	static FILE *fps[FOPEN_MAX];

	puts("test2");

	max = TMP_MAX - 2;
	if (max > FOPEN_MAX)
		max = FOPEN_MAX - 3;
	if (max > 32)
		max = 32;

	for (i = 0; i < max; i++)
		assert(fps[i] = tmpfile());

	for (i = 0; i < max; i++)
		assert(fclose(fps[i]) == 0);
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
