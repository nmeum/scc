#include <stddef.h>

extern int enadebug;

#ifndef NDEBUG
#define DBG(...) dbg(__VA_ARGS__)
#define DBGON() (enadebug = 1)
#else
#define DBG(...)
#define DBGON()
#endif

struct items {
	char **s;
	unsigned n;
};

#ifdef CLOCKS_PER_SEC
struct fprop {
	unsigned uid;
	unsigned gid;
	unsigned long mode;
	long size;
	time_t time;
};
#endif

typedef struct alloc Alloc;

void die(const char *, ...);
void dbg(const char *, ...);
void newitem(struct items *, char *);
void *xmalloc(size_t);
void *xcalloc(size_t, size_t);
char *xstrdup(const char *);
void *xrealloc(void *, size_t);
Alloc *alloc(size_t, size_t);
void dealloc(Alloc *);
void *new(Alloc *);
void delete(Alloc *, void *);
int casecmp(const char *, const char *);
unsigned genhash(char *);
char *canonical(char *);

#ifdef CLOCKS_PER_SEC
long long fromepoch(time_t);
time_t totime(long long);
int getstat(char *, struct fprop *);
int setstat(char *, struct fprop *);
#endif
