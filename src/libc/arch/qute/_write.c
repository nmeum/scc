#include <errno.h>
#include <stddef.h>

extern int qute_write(int fd, void*, size_t);

int
_write(int fd, void *buf, size_t count)
{
	int nwritten = qute_write(fd, buf, count);
	if (nwritten < 0) {
		errno = nwritten * -1;
		return -1;
	}

	return nwritten;
}
