#include <errno.h>
#include <stddef.h>

extern int qute_read(int fd, void*, size_t);

int
_read(int fd, void *buf, size_t count)
{
	int n = qute_read(fd, buf, count);
	if (n < 0) {
		errno = n * -1;
		return -1;
	}

	return n;
}
