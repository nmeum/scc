/* passes */
void pass1(int argc, char *argv[]);
void pass2(int argc, char *argv[]);
void pass3(int argc, char *argv[]);
void pass4(int argc, char *argv[]);
void pass5(int argc, char *argv[]);

/* main.c */
void error(char *fmt, ...);
char *nextarg(char **argp, char ***argv);

/* symbol.c */
int hasref(char *name);
Symbol *lookupsym(char *name);
int moreundef(void);
void listundef(void);
Symbol *define(Symbol *osym, Obj *obj);
void debugsym(void);

/* section.c */
Section *lookupsec(char *name);
void copy(Obj *obj, Section *osec, Section *sec);
void grow(Section *sec, int nbytes);
void merge(Section *seg);
void debugsec(void);

/* globals */
extern char *libpaths[];
extern char *filename, *membname;
extern int sflag;
extern int xflag;
extern int Xflag;
extern int rflag;
extern int dflag;
extern int gflag;
extern char *output, *entry;
extern Obj *objhead;
extern Section debug, text, rodata, data, bss;
