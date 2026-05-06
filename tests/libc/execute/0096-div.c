#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

/*
output:
testing
test1
test2
test3
test4
done
end:
*/

static void
test1(void)
{
	div_t d;

	puts("test1");

	d = div(8, 4);
	assert(d.quot == 2 && d.rem == 0);

	d = div(-10, 3);
	assert(d.quot == -3 && d.rem == -1);

	d = div(10, -3);
	assert(d.quot == -3 && d.rem == 1);

	d = div(-11, -3);
	assert(d.quot == 3 && d.rem == -2);
}

static void
test2(void)
{
	ldiv_t ld;

	puts("test2");

	ld = ldiv(8, 4);
	assert(ld.quot == 2 && ld.rem == 0);


	ld = ldiv(-10, 3);
	assert(ld.quot == -3 && ld.rem == -1);

	ld = ldiv(10, -3);
	assert(ld.quot == -3 && ld.rem == 1);

	ld = ldiv(-11, -3);
	assert(ld.quot == 3 && ld.rem == -2);
}

static void
test3(void)
{
	lldiv_t lld;

	puts("test3");

	lld = lldiv(8, 4);
	assert(lld.quot == 2 && lld.rem == 0);


	lld = lldiv(-10, 3);
	assert(lld.quot == -3 && lld.rem == -1);

	lld = lldiv(10, -3);
	assert(lld.quot == -3 && lld.rem == 1);

	lld = lldiv(-11, -3);
	assert(lld.quot == 3 && lld.rem == -2);
}

static void
test4(void)
{
	imaxdiv_t md;

	puts("test4");

	md = imaxdiv(8, 4);
	assert(md.quot == 2 && md.rem == 0);

	md = imaxdiv(-10, 3);
	assert(md.quot == -3 && md.rem == -1);

	md = imaxdiv(10, -3);
	assert(md.quot == -3 && md.rem == 1);

	md = imaxdiv(-11, -3);
	assert(md.quot == 3 && md.rem == -2);
}

int
main(void)
{
	puts("testing");
	test1();
	test2();
	test3();
	test4();
	puts("done");
}
