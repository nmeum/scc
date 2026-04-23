/*
output:
testing
difftime=1
done
end:
*/
#include <stdio.h>
#include <time.h>

int
main(void)
{
	time_t t1, t2;
	clock_t k1, k2;

	t1 = time(NULL);
	puts("testing");

	for (k1 = k2 = clock(); (k2 - k1) / CLOCKS_PER_SEC < 1; k2 = clock())
		;
	t2 = time(NULL);
	printf("difftime=%d\n",  difftime(t2, t1) >= 1);

	puts("done");

	return 0;
}
