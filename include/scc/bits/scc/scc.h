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

void die(const char *fmt, ...);
void dbg(const char *fmt, ...);
void newitem(struct items *items, char *item);
void *xmalloc(size_t size);
void *xcalloc(size_t nmemb, size_t size);
char *xstrdup(const char *s);
void *xrealloc(void *buff, size_t size);
Alloc *alloc(size_t size, size_t nmemb);
void dealloc(Alloc *allocp);
void *new(Alloc *allocp);
void delete(Alloc *allocp, void *p);
int casecmp(const char *s1, const char *s2);
unsigned genhash(char *name);
char *canonical(char *);

#ifdef CLOCKS_PER_SEC
long long fromepoch(time_t);
time_t totime(long long);
int getstat(char *, struct fprop *);
int setstat(char *, struct fprop *);
#endif
