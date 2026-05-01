#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
output:
testing
done
end:
*/

int putenv(char *);

int
main(void)
{
	char *s;

	puts("testing");
	s = getenv("THIS_CANNOT_BE_A_ENV_CAR");
	assert(s == NULL);

#if defined(__unix__) || defined(__SCC_PUTENV__)
	putenv("AVAR=avalue");
	s = getenv("AVAR");
	assert(strcmp(s, "avalue") == 0);
#endif
	puts("done");

	return 0;
}
