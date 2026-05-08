#ifdef stdin
int copysec(Mapsec *, FILE *);
int setidx32(int, long, char *[], long [], FILE *);
int getidx32(int, long *, char ***, long **, FILE *);
#endif

/* common functions */
int pack(int order, unsigned char *dst, char *fmt, ...);
int unpack(int order, unsigned char *src, char *fmt, ...);
