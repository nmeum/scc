#include <stdio.h>
#include <stdlib.h>

/*
output:
testing
hello
done
end:
*/

int
main(void)
{
	puts("testing");
	system("echo hello");
	puts("done");

	return 0;
}
