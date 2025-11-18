/* passes */
void pass1(int, char *[]);
void pass2(int, char *[]);
void pass3(int, char *[]);
void pass4(int, char *[]);
void pass5(int, char *[]);

/* main.c */
void error(char *, ...);
char *nextarg(char **, char ***);

/* symbol.c */
int hasref(char *);
Symbol *lookupsym(char *);
int moreundef(void);
void listundef(void);
Symbol *define(Symbol *, Obj *);
void debugsym(void);

/* section.c */
Section *lookupsec(char *);
void copy(Obj *, Section *, Section *);
void grow(Section *, int);
void merge(Section *);
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
