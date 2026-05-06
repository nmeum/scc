#include <errno.h>
#include <stdlib.h>
#include <string.h>

extern char **_environ;

int
putenv(char *name)
{
	char **p, *s;
	size_t siz, len, cnt;
	static char **lastenv;

	if ((s = strchr(name, '=')) == NULL) {
		errno = EINVAL;
		return -1;
	}
	len = s - name;

	for (p = _environ; *p; ++p) {
		if (!strncmp(name, *p, len) && (*p)[len] == '=') {
			*p = name;
			return 0;
		}
	}

	cnt = p - _environ;
	siz = (cnt + 2) * sizeof(char **);

	if ((p = realloc(lastenv, siz)) == NULL)
		return -1;
	if (!lastenv)
		memcpy(p, _environ, cnt * sizeof(char **));
	lastenv = _environ = p;

	p[cnt] = name;
	p[cnt+1] = NULL;

	return 0;
}
