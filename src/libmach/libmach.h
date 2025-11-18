#ifdef stdin
int copysec(Mapsec *, FILE *);
#endif

/* common functions */
int pack(int order, unsigned char *dst, char *fmt, ...);
int unpack(int order, unsigned char *src, char *fmt, ...);
