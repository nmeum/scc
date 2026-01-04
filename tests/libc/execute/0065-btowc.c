#include <assert.h>
#include <stdio.h>
#include <wchar.h>

/*
output:
testing
done
end:
*/

int
main(void)
{
	puts("testing");
	assert(btowc('a') == 'a');
	assert(btowc(EOF) == -1);
	assert(btowc('\x99') == -1);
	puts("done");

	return 0;
}
