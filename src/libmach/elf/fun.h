int elfnew(Obj *, int);
int elfread(Obj *, FILE *);
int elfsetidx(int, long, char **, long *, FILE *);
int elfgetidx(int, long *, char ***, long **, FILE *);
int elfpc2line(Obj *, unsigned long long , char *, int *);
int elfstrip(Obj *);
void elfdel(Obj *);
int elfwrite(Obj *, Map *, FILE *);
int elfprobe(unsigned char *, char **);
int elftype(char *);

Symbol *elfgetsym(Obj *, int *, Symbol *);
Section *elfgetsec(Obj *, int *, Section *);
Map *elfloadmap(Obj *, FILE *);
