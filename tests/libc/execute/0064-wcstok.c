#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

/*
output:
testing
test1
one
two
three
four
test2
one
three
test3
one
done
end:
*/

void
test(char *msg, wchar_t *fmt)
{
	wchar_t *s, *p, buff[50];

	puts(msg);

	wcscpy(buff, fmt);
	for (s = wcstok(buff, L"-+", &p); s; s = wcstok(NULL, L"+-", &p)) {
		switch (*s) {
		case L'1':
			puts("one");
			break;
		case L'2':
			puts("two");
			break;
		case L'3':
			puts("three");
			break;
		case L'4':
			puts("four");
			break;
		default:
			puts("error");
			break;
		}
	}
}

int
main()
{
	puts("testing");
	test("test1", L"-+1--2++3+-4");
	test("test2", L"1--+-+-+-3+-");
	test("test3", L"1");
	puts("done");
	return 0;
}
