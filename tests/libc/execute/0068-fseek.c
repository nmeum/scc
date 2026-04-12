/*
output:
202
end:
*/

#include <stdio.h>

int
main(void)
{
	FILE *fp = fopen(__FILE__, "r");
	if (fp == 0) {
		perror(__FILE__);
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	printf("%ld\n", ftell(fp));
}
