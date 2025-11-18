/*
 * First 3 bits of flags in segments and symbols are for the
 * type of segment
 */
enum symflags {
	FREG    = 1 << 0,
	FSECT   = 1 << 1,
	FSYM    = 1 << 2,
	FCOMMON = 1 << 3,
	FEXTERN = 1 << 4,
	FDEF    = 1 << 5,
	FGLOBAL = 1 << 6,
	FABS    = 1 << 7,
};

enum common_args {
	AIMM = 1,
	ASTR,
	AREG,
	ANUMBER,
	AIMM2,
	AIMM3,
	AIMM5,
	AIMM8,
	AIMM16,
	AIMM32,
	AIMM64,
	AINDIR,
	AINDEX,
	ADIRECT,
	AREG_OFF,
	ASYM,
	AOPT,
	AREP,
	AMAX,
};

enum tokens {
	EOS = -1,
	IDEN = 1,
	NUMBER,
	REG,
	STRING,
	MINUS,
	SHL,
	SHR,
	GE,
	LE,
};

#define MAXSYM 63

typedef struct reloc Reloc;
typedef struct ins Ins;
typedef struct op Op;
typedef struct node Node;
typedef void Format(Op *, Node **);

struct line {
	char *label;
	char *op;
	char *args;
};

struct ins {
	int begin, end;
	char *str;
};

struct reloc {
	size_t offset;
	Symbol *sym;
	unsigned char flags;
	unsigned char size;
	unsigned char nbits;
	unsigned char shift;
};

struct op {
	unsigned char flags;
	unsigned char size;
	void (*format)(Op *, Node **);
	unsigned char *bytes;
	unsigned char *args;
};

struct node {
	unsigned char op;
	unsigned char addr;
	struct symbol *sym;
	struct node *left;
	struct node *right;
};

union yylval {
	unsigned long long val;
	Symbol *sym;
};

/* symbol.c */
void cleansecs(void);
void ibinfmt(void);
void emit(char *, int);
Section *defsec(char *, char *);
Symbol *tmpsym(unsigned long long);
void killtmp(void);
int toobig(Node *, int);
void dumpstab(char *);
Symbol *lookup(char *);
Symbol *deflabel(char *);
unsigned long long getpc(void);

/* parser.c */
Node **getargs(char *);
void error(char *, ...);
/* Avoid errors in files where stdio is not included */
#ifdef stdin
int nextline(struct line *);
#endif
void unexpected(void);
void expect(int);
int next(void);
#define accept(t) (yytoken == (t) ? next() : 0)
void regctx(int mode);
Node *getreg(void);
Node *operand(char **);
void addinput(char *);
int delinput(void);
int ahead(void);

/* expr.c */
Node *expr(void);
void deltree(Node *);
Node *node(int, Node *, Node *);

/* proc.c */
void iarch(void);
int match(Op *, Node **);
Node *moperand(void);

/* ins.c */
char *tobytes(unsigned long long, int, int);

/* binfmt.c */
void writeout(char *);

/*
 * Definition of global variables
 */
extern unsigned long M, S, K;
extern short hashmap[];
extern Section *cursec;
extern Ins instab[];
extern Op optab[];
extern int pass;
extern unsigned long long maxaddr;
extern int endian;
extern Symbol *linesym;
extern char *infile, *outfile;
extern int endpass;
extern int yytoken;
extern size_t yylen;
extern union yylval yylval;
extern char yytext[];
