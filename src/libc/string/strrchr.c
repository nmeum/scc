#include <string.h>

#undef strrchr

char *
strrchr(const char *s, int c)
{
	const char *t;

	for (t = s; *t; ++t)
		;
	while (t > s && *t != c)
		--t;

	return (*t == c) ? (char *) t : NULL;
}
