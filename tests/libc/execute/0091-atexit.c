#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
output:
testing
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun1
fun2
fun3
done
end:
*/

static void
fun1(void)
{
	puts("fun1");
}

static void
fun2(void)
{
	puts("fun2");
}

static void
fun3(void)
{
	puts("fun3");
	puts("done");
	fflush(stdout);
	_Exit(0);
}

static void
fun4(void)
{
	puts("fun4");
}

int
main(void)
{
	int i, r;

	puts("testing");
	r = atexit(fun4);
	assert(r == 0);

	r = atexit(fun3);
	assert(r == 0);

	r = atexit(fun2);
	assert(r == 0);


	for (i = 0; i < 29; i++) {
		r = atexit(fun1);
		assert(r == 0);
	}
	exit(EXIT_SUCCESS);

	printf("failed");
	exit(EXIT_FAILURE);

	return 1;
}
