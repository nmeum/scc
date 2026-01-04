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
	assert(wctob(L'a') == 'a');
	assert(wctob(WEOF) == -1);
	assert(wctob(134) == -1);
	puts("done");

	return 0;
}
