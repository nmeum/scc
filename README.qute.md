This patch contains preliminary support for using SCC's libc with Qute <https://git.8pit.net/qute/>.

To compile a libc.a for Qute, first compile SCC:

	$ guix shell -CPW -D simple-cc gdb
	[env]$ make -j10 CFLAGS="-g -O0" SCCMAKE=make CC=gcc HOSTCC=gcc

Afterward, build Qute's libc.a with SCC:

	$ make -f main.mk -j10 CFLAGS="-g -O0" SCCMAKE=make CC=$(pwd)/bin/scc CONF=amd64-qute libc

This will generate `./lib/scc/amd64-qute/libc.a` which can then be preloaded using Qute.

---

Consider the following example:

	#include <assert.h>
	#include <stdlib.h>

	extern void qute_make_symbolic(void *ptr, size_t nelem, size_t elsiz, const char *name);

	int main(void) {
		int a;
		qute_make_symbolic(&a, 1, sizeof(a), "a");

		if (a <= 0)
			exit(0);
		assert(a > 0);
		return 0;
	}

Compile this as follows to QBE using SCC:

	$ ./bin/scc -c -o test.qbe test.c -R

Afterward, execute the resulting `test.qbe` file using Qute:

	$ qute-symex -p ./lib/scc/amd64-qute/libc.a test.qbe
