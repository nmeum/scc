#include <assert.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

/*
output:
testing
done
end:
*/

static int neg, pos;

static int
setup(void)
{
	neg = LC_ALL;
	if (neg > LC_COLLATE)
		neg = LC_COLLATE;
	if (neg > LC_CTYPE)
		neg = LC_CTYPE;
	if (neg > LC_MONETARY)
		neg = LC_MONETARY;
	if (neg > LC_NUMERIC)
		neg = LC_NUMERIC;
	if (neg > LC_TIME)
		neg = LC_TIME;
	--neg;

	pos = LC_ALL;
	if (pos < LC_COLLATE)
		pos = LC_COLLATE;
	if (pos < LC_CTYPE)
		pos = LC_CTYPE;
	if (pos < LC_MONETARY)
		pos = LC_MONETARY;
	if (pos < LC_NUMERIC)
		pos = LC_NUMERIC;
	if (pos < LC_TIME)
		pos = LC_TIME;
	++pos;

	return 0;
}

static void
run(void)
{
	char *l1, *l2;

	l1 = setlocale(LC_ALL, NULL);
	assert(strcmp(l1, "C") == 0);

	l1 = setlocale(pos, "C");
	l2 = setlocale(neg, "C");

	assert(l1 == NULL);
	assert(l2 == NULL);

	setlocale(LC_ALL, "");
}

int
main(void)
{
	puts("testing");
	setup();
	run();
	puts("done");

	return 0;
}
