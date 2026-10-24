#include <string.h>
#include <stdlib.h>

#undef strdup

char *
strdup(const char *s)
{
	char *newstr;
	size_t len = strlen(s);

	if ((newstr = malloc(len + 1)) == NULL)
		return NULL;
	return memcpy(newstr, s, len + 1);
}
