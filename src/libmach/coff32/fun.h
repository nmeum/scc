int coff32new(Obj *, int);
int coff32read(Obj *, FILE *);
int coff32setidx(int, long, char **, long *, FILE *);
int coff32getidx(long *, char ***, long **, FILE *);
int coff32pc2line(Obj *, unsigned long long, char *, int *);
int coff32strip(Obj *);
void coff32del(Obj *);
int coff32write(Obj *, Map *, FILE *);
int coff32probe(unsigned char *, char **);
int coff32type(char *);

int coff32xgetidx(int, long *, char ***, long **, FILE *);

Symbol *coff32getsym(Obj *, int *, Symbol *);
Symbol *coff32setsym(Obj *, int *, Symbol *);
Section *coff32getsec(Obj *, int *, Section *);
Section *coff32setsec(Obj *, int *, Section *);
Map *coff32loadmap(Obj *, FILE *);
