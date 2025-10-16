#define LDBIN "ld.lld"
#define ASBIN "clang"

/* configure below your standard sys include paths */
char *sysincludes[] = {
	"%p/include/scc/bits/%a/",
	"%p/include/scc/bits/%s/",
	"%p/include/scc/bits/%s/%a/",
	"%p/include/scc",
	NULL
};

/* configure below your system linker command line */
char *ldcmd[] = {
	"-static",
	"-z","nodefaultlib",
	%NOPIE%
	"-o","%o",
	"-L","%p/lib/scc/%a-%s",
	"%p/lib/scc/%a-%s/crt.o",
	"%c",
	"-lc",
	"-lcrt",
        NULL
};

/* configure below your system assembler command line */
char *ascmd[] = {
	"-x","assembler",
	"-c",
	"-o","%o",
	"-",
	NULL
};
