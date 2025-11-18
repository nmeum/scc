int elfnew(Obj *, int);
int elfread(Obj *, FILE *);
int elfsetidx(long, char **, long *, FILE *);
int elfgetidx(long *, char ***, long **, FILE *);
int elfpc2line(Obj *, unsigned long long , char *, int *);
int elfstrip(Obj *);
void elfdel(Obj *);
int elfwrite(Obj *, Map *, FILE *);
int elfprobe(unsigned char *, char **);
int elftype(char *);

int elfxsetidx(int long , char *[], long [], FILE *);
int elfxgetidx(int, long *, char ***, long **, FILE *);

Symbol *elfgetsym(Obj *, int *, Symbol *);
Section *elfgetsec(Obj *, int *, Section *);
Map *elfloadmap(Obj *, FILE *);
