#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
output:
testing
done
end:
*/

int
main(void)
{
	char buff[40], *s;
	FILE *fp;

	puts("testing");
	fp = fopen("__NOT_A_FILE", "w");
	assert(fp);
	fputs("Hello\n", fp);
	fflush(fp);
	assert(ferror(fp) == 0);
	fclose(fp);
	assert(rename("__NOT_A_FILE", "__NOT_OTHER_FILE") == 0);

	fp = fopen("__NOT_OTHER_FILE", "r");
	assert(fp);
	s = fgets(buff, sizeof(buff), fp);
	assert(s != NULL);
	assert(strcmp(s, "Hello\n") == 0);
	fclose(fp);

	assert(remove("__NOT_OTHER_FILE") == 0);
	puts("done");

	return 0;
}
