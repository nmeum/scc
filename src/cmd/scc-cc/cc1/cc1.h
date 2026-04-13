#include <stdint.h>

#define INPUTSIZ LINESIZ

#define GLOBALCTX 0
#define PARAMCTX  1

#define NR_USWITCHES 20

#define FAIL   1
#define NOFAIL 0

#define EQUAL  0
#define EQUIV  1

/*
 * Definition of enumerations
 */
enum {
	NOALLOC,
	ALLOC
};

enum typeprops {
	TDEFINED = 1 << 0,    /* type defined */
	TSIGNED  = 1 << 1,    /* signedness of the type */
	TINTEGER = 1 << 2,    /* the type is INT of enum */
	TARITH   = 1 << 3,    /* the type is INT, ENUM or FLOAT */
	TAGGREG  = 1 << 4,    /* the type is struct or union */
	TK_R     = 1 << 5,    /* this is a K&R-function */
	TELLIPSIS= 1 << 6,    /* this function has an ellipsis par */
	TFUNDEF  = 1 << 7,    /* function definition */
};

enum inputtype {
	IMACRO = 1 << 0,      /* macro expansion type */
	IFILE  = 1 << 1,      /* input file type */
	ISTDIN = 1 << 2,      /* stdin type */
	IPARAM = 1 << 3,      /* macro param expansion */
	IEOF   = 1 << 4,      /* EOF mark */
	ITYPE  = IMACRO | IFILE | ISTDIN | IPARAM,
};

/* data type letters */
enum ns {
	L_INT8      = 'C',
	L_INT16     = 'I',
	L_INT32     = 'W',
	L_INT64     = 'Q',
	L_UINT8     = 'K',
	L_UINT16    = 'N',
	L_UINT32    = 'Z',
	L_UINT64    = 'O',
	L_BOOL      = 'B',

	L_FLOAT     = 'J',
	L_DOUBLE    = 'D',
	L_LDOUBLE   = 'H',

	L_ELLIPSIS  = 'E',
	L_VOID      = '0',
	L_POINTER   = 'P',
	L_FUNCTION  = 'F',
	L_ARRAY     = 'V',
	L_UNION     = 'U',
	L_STRUCT    = 'S',
	L_VA_ARG    = '1',
};

/* recovery points */
enum {
	END_DECL,
	END_LDECL,
	END_COMP,
	END_COND
};

/* type constructors */
enum typeop {
	FTN = 1,
	PTR,
	ARY,
	KRFTN
};

/* namespaces */
enum namespaces {
	NS_DUMMY,
	NS_IDEN,
	NS_TAG,
	NS_LABEL,
	NS_CPP,
	NS_KEYWORD,
	NS_CPPCLAUSES,
	NS_MACROPAR,

	/*
	 * This must be the last constant of the enum definition
	 * because it marks the beginning of the independent
	 * struct namespaces
	 */
	NS_STRUCTS,
};

/* symbol flags */
enum {
	SAUTO     = 1 << 0,
	SREGISTER = 1 << 1,
	SDECLARED = 1 << 2,
	SFIELD    = 1 << 3,
	SEXTERN   = 1 << 4,
	SUSED     = 1 << 5,
	SCONSTANT = 1 << 6,
	SGLOBAL   = 1 << 7,
	SPRIVATE  = 1 << 8,
	SLOCAL    = 1 << 9,
	SEMITTED  = 1 << 10,
	SDEFINED  = 1 << 11,
	SRSTRING  = 1 << 11,
	SSTRING   = 1 << 12,
	STYPEDEF  = 1 << 13,
	SINITLST  = 1 << 14,
	SHASINIT  = 1 << 15,
	SVARIADIC = 1 << 15,
};

/* node flags */
enum {
	NLVAL   = 1 << 0,
	NCONST  = 1 << 1,
	NEFFECT = 1 << 2,
	NDECAY  = 1 << 3,
};

/* lexer mode, compiler or preprocessor directive */
enum {
	CCMODE,
	CPPMODE
};

/* input tokens */
enum tokens {
	CONST      = 1 << 0,      /* type qualifier tokens are used as flags */
	RESTRICT   = 1 << 1,
	VOLATILE   = 1 << 2,
	INLINE     = 1 << 3,
	TQUALIFIER = 1 << 7,
	MACROPAR   = 17,
	CONCAT     = 18,
	STRINGIZE  = 19,
	TYPE       = 129,
	IDEN,
	SCLASS,
	CONSTANT,
	STRING,
	SIZEOF,
	INDIR,
	INC,
	DEC,
	SHL,
	SHR,
	LE,
	GE,
	EQ,
	NE,
	AND,
	OR,
	MUL_EQ,
	DIV_EQ,
	MOD_EQ,
	ADD_EQ,
	SUB_EQ,
	AND_EQ,
	XOR_EQ,
	OR_EQ,
	SHL_EQ,
	SHR_EQ,
	ELLIPSIS,
	CASE,
	DEFAULT,
	IF,
	ELSE,
	SWITCH,
	WHILE,
	DO,
	FOR,
	GOTO,
	VOID,
	FLOAT,
	INT,
	BOOL,
	VA_LIST,
	STRUCT,
	UNION,
	CHAR,
	DOUBLE,
	SHORT,
	LONG,
	LLONG,
	COMPLEX,
	TYPEDEF,
	EXTERN,
	STATIC,
	AUTO,
	REGISTER,
	ENUM,
	TYPEIDEN,
	UNSIGNED,
	SIGNED,
	CONTINUE,
	BREAK,
	RETURN,
	DEFINE,
	DEFINED,
	INCLUDE,
	LINE,
	PRAGMA,
	ERROR,
	IFDEF,
	ELIF,
	IFNDEF,
	UNDEF,
	ENDIF,
	BUILTIN,
	EOFTOK
};

/* operations */
enum op {
	OADD,
	OMUL,
	OSUB,
	OINC,
	ODEC,
	ODIV,
	OMOD,
	OSHL,
	OSHR,
	OBAND,
	OBXOR,
	OBOR,
	OSNEG,
	ONEG,
	OCPL,
	OAND,
	OOR,
	OEQ,
	ONE,
	OLT,
	OGE,
	OLE,
	OGT,
	OASSIGN,
	OA_MUL,
	OA_DIV,
	OA_MOD,
	OA_ADD,
	OA_SUB,
	OA_SHL,
	OA_SHR,
	OA_AND,
	OA_XOR,
	OA_OR,
	OADDR,
	OCOMMA,
	OCAST,
	OPTR,
	OSYM,
	OASK,
	OCOLON,
	OFIELD,
	OLABEL,
	ODEFAULT,
	OCASE,
	OJUMP,
	OBRANCH,
	OEXPR,
	OEFUN,
	OELOOP,
	OBLOOP,
	OFUN,
	OPAR,
	OCALL,
	OCALLE,
	ORET,
	ODECL,
	OBSWITCH,
	OESWITCH,
	OINIT,
	OBUILTIN,
	OTYP,
};

/*
 * Definition of structures
 */
typedef struct type Type;
typedef struct symbol Symbol;
typedef struct swtch Switch;
typedef struct node Node;
typedef struct macro Macro;
typedef struct input Input;
typedef struct arch Arch;
typedef uint32_t Rune;

struct limits {
	union {
		unsigned long long i;
		double f;
	} max;
	union {
		unsigned long long i;
		double f;
	} min;
};

struct builtin {
	char *str;
	Node *(*fun)(Symbol *);
};

struct type {
	unsigned char op;           /* type builder operator */
	int ns;                     /* namespace for struct members */
	short id;                   /* type id, used in dcls */
	char letter;                /* letter of the type */
	unsigned char prop;         /* type properties */
	unsigned char align;        /* align of the type */
	unsigned long size;         /* sizeof the type */
	Type *type;                 /* base type */
	Symbol *tag;                /* symbol of the strug tag */
	union {
		Type **pars;            /* Function type parameters */
		Symbol **fields;        /* fields of aggregate type */
	} p;
	union {
		unsigned char rank;     /* conversion rank */
		long long elem;         /* number of type parameters */
	} n;
	Type *next;                 /* local list pointer */
	Type *h_next;               /* hash collision list */
};

struct symbol {
	unsigned char ctx;
	unsigned char hide;
	int ns;
	unsigned short id;
	unsigned short flags;
	char *name;
	Type *type;
	unsigned char token;
	union {
		long long i;
		unsigned long long u;
		float f;
		double d;
		long double ld;
		char *s;
		Rune *rs;
		unsigned char token;
		Node **init;
		Symbol **pars;
		Node *(*fun)(Symbol *);
	} u;
	struct symbol *next;
	struct symbol *hash;
};

struct node {
	unsigned char op;
	unsigned char flags;
	Type *type;
	Symbol *sym;
	struct node *left, *right;
};

struct swtch {
	short nr;
	char hasdef;
};

struct arch {
	Type voidtype;
	Type pvoidtype;
	Type booltype;
	Type schartype;
	Type uchartype;
	Type chartype;
	Type ushorttype;
	Type shorttype;
	Type uinttype;
	Type inttype;
	Type longtype;
	Type ulongtype;
	Type ullongtype;
	Type llongtype;
	Type floattype;
	Type doubletype;
	Type ldoubletype;
	Type sizettype;
	Type pdifftype;
	Type ellipsistype;
	Type va_type;
	Type va_list_type;
	Type wchartype;

	int (*valid_va_list)(Type *tp);
};

struct yystype {
	Symbol *sym;
	unsigned char token;
};

#ifdef NR_MACROARG
struct macro {
	Symbol *sym;
	char *fname;
	char **arglist;
	char *buffer;
	char *def;
	char *arg;
	int bufsiz;
	int argsiz;
	int npars;
	Symbol *hideset[NR_MACROARG];
};
#endif

#ifdef stdin
struct input {
	char flags;
	unsigned lineno;
	char *filenam;
	FILE *fp;
	Macro *macro;
	char *line, *begin, *p;
	struct input *next;
};
#endif

/* error.c */
void error(char *, ...);
void warn(char *, ...);
void unexpected(void);
void errorp(char *, ...);
void cpperror(char *, ...);
Type *deftype(Type *);

/* types.c */
int eqtype(Type *, Type *, int);
Type *ctype(int, int, int);
Type *mktype(Type *, int, long long, Type *[]);
Type *duptype(Type *);
struct limits *getlimits(Type *);
void typesize(Type *);
void flushtypes(void);

/* symbol.c */
void dumpstab(Symbol **, char *);
Symbol *lookup(int, char *, int);
Symbol *nextsym(Symbol *, int);
Symbol *install(int, Symbol *);
Symbol *newsym(int, char *);
void pushctx(void), popctx(void);
void killsym(Symbol *);
Symbol *newlabel(void);
void builtins(struct builtin *);
Symbol *newstring(char *, size_t);
Symbol *newrstring(Rune *, size_t);
unsigned newid(void);
void isyms(void);

/* stmt.c */
void compound(Symbol *, Symbol *, Switch *);

/* decl.c */
Type *typename(void);
void decl(void);

/* lex.c */
int ahead(void);
int next(void);
void expect(int);
void discard(void);
int moreinput(void);
int addinput(int, void *, int);
void delinput(void);
void setsafe(int);
void setloc(char *, unsigned);
#define accept(t) ((yytoken == (t)) ? next() : 0)

/* code.c */
Node *prtree(char *, Node *);
void emit(int, void *);
Node *node(int, Type *, Node *, Node *);
Node *varnode(Symbol *);
Node *constnode(Symbol *);
Node *sizeofnode(Type *);
Node *offsetnode(Symbol *,  Type *);
Node *addrnode(unsigned long long);
void freetree(Node *);
void icode(void);
Node *zeronode(Type *);
#define BTYPE(np) ((np)->type->op)

/* fold.c */
Node *simplify(Node *);
unsigned long long ones(int);

/* expr.c */
Node *decay(Node *), *negate(Node *np), *assign(void);
Node *convert(Node *, Type *, int);
Node *constexpr(void), *condexpr(int), *expr(void);
int isnodecmp(int);
int negop(int);
int cmpnode(Node *, unsigned long long);
int power2node(Node *, int *);

/* init.c */
void initializer(Symbol *);

/* cpp.c */
void icpp(void);
int cpp(void);
int expand(Symbol *);
void incdir(char *);
void outcpp(void);
void defdefine(char *, char *, char *);
void undefmacro(char *);
void ppragmaln(void);
void delmacro(Macro *);
Macro *newmacro(Symbol *);
Node *defined(void);


/* builtin.c */
void ibuilts(void);

/* arch.c */
void iarch(void);
int valid_va_list(Type *);

/* architectures */
Arch *amd64_sysv(void);
Arch *z80_scc(void);
Arch *arm64_sysv(void);
Arch *riscv64_sysv(void);
Arch *i386_sysv(void);

/*
 * Definition of global variables
 */
extern struct yystype yylval;
extern char yytext[];
extern int yytoken;
extern unsigned short yylen;
extern int disexpand, disstring;
extern unsigned cppctx;
extern Input *input;
extern int lexmode, namespace;
extern int onlycpp, onlyheader;
extern unsigned curctx;
extern Symbol *curfun, *zero, *one;
extern unsigned lineno;
extern char filenam[];
extern char *architecture;

extern Type *voidtype, *pvoidtype, *booltype,
            *uchartype,   *chartype, *schartype,
            *uinttype,    *inttype,
            *sizettype, *pdifftype,
            *ushorttype,   *shorttype,
            *longtype,    *ulongtype,
            *ullongtype,  *llongtype,
            *floattype,   *doubletype,  *ldoubletype,
            *ellipsistype, *va_list_type, *va_type,
            *wchartype;
