#include <wchar.h>

#undef wcstok

wchar_t *
wcstok(wchar_t * restrict s1, const wchar_t * restrict s2,
       wchar_t **restrict ptr)
{
	wchar_t *line;

	if (s1)
		line = s1;
	else
		line = *ptr;

	if (!line)
		return NULL;

	s1 = line + wcsspn(line, s2);
	if (*s1 == L'\0')
		return *ptr = NULL;

	line = s1 + wcscspn(s1, s2);
	if (*line == '\0')
		line = NULL;
	else
		*line++ = L'\0';
	*ptr = line;

	return s1;
}
