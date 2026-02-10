#define ASLABEL 0

#ifdef NDEBUG
#define PRCFG(msg)
#define PRTREE(msg)
#else
#define PRCFG(msg) (enadebug ? prcfg(msg) : NULL)
#define PRTREE(msg) (enadebug ? prforest(msg) : NULL)
#endif

enum iflags {
	BBENTRY =    1,        /* basic block entry */
	BBEXIT  =    2,        /* basic block exit */
};

enum tflags {
	SIGNF   =     1 << 0,  /* Signed type */
	INTF    =     1 << 1,  /* integer type */
	FLOATF  =     1 << 2,  /* float type */
	STRF    =     1 << 3,  /* string */
	AGGRF   =     1 << 4,  /* aggregate */
	FUNF    =     1 << 5,  /* function */
	PARF    =     1 << 6,  /* parameter */
	INITF   =     1 << 7,  /* initializer flag */
	ELLIPS  =     1 << 8,  /* vararg function */
	ARRF    =     1 << 9,  /* array flag */
	PTRF    =     1 << 10, /* pointer flag */
};

enum sclass {
	SAUTO     = 'A',
	SREG      = 'R',
	SLABEL    = 'L',
	SINDEX    = 'I',
	STMP      = 'N',
	SGLOB     = 'G',
	SEXTRN    = 'X',
	SPRIV     = 'Y',
	SLOCAL    = 'T',
	SMEMB     = 'M',
	SCONST    = '#',
	STRING    = '"',
	SNONE     = 0 /* cc2 relies on SNONE being 0 in nextpc() */
};

enum types {
	ELLIPSIS = 'E',
	INT8     = 'C',
	INT16    = 'I',
	INT32    = 'W',
	INT64    = 'Q',
	UINT8    = 'K',
	UINT16   = 'N',
	UINT32   = 'Z',
	UINT64   = 'O',
	POINTER  = 'P',
	FUNCTION = 'F',
	VECTOR   = 'V',
	UNION    = 'U',
	STRUCT   = 'S',
	BOOL     = 'B',
	FLOAT    = 'J',
	DOUBLE   = 'D',
	LDOUBLE  = 'H',
	VOID     = '0'
};

enum op {
	/* kind of operand */
	/* operands */
	OMEM     = 'M',
	OINDEX   = 'I',
	OTMP     = 'N',
	OAUTO    = 'A',
	OREG     = 'R',
	OMREG    = 'G',
	OCONST   = '#',
	OSTRING  = '"',
	OLOAD    = 'D',
	OLABEL   = 'L',
	OADD     = '+',
	OSUB     = '-',
	OMUL     = '*',
	OMOD     = '%',
	ODIV     = '/',
	OSHL     = 'l',
	OSHR     = 'r',
	OLT      = '<',
	OGT      = '>',
	OLE      = '[',
	OGE      = ']',
	OEQ      = '=',
	ONE      = '!',
	OBAND    = '&',
	OBOR     = '|',
	OBXOR    = '^',
	OCPL     = '~',
	OASSIG   = ':',
	OSNEG    = '_',
	OCALL    = 'c',
	OCALLE   = 'z',
	OPAR     = 'p',
	OFIELD   = '.',
	OCOMMA   = ',',
	OASK     = '?',
	OCOLON   = ' ',
	OADDR    = '\'',
	OAND     = 'a',
	OOR      = 'o',
	ONEG     = 'n',
	OPTR     = '@',
	OCAST    = 'g',
	OINC     = 'i',
	ODEC     = 'd',
	OBUILTIN = 'm',
	/*statements */
	ONOP     = 'q',
	OJMP     = 'j',
	OBRANCH  = 'y',
	ORET     = 'h',
	OBLOOP   = 'b',
	OELOOP   = 'e',
	OCASE    = 'v',
	ODEFAULT = 'f',
	OBSWITCH = 's',
	OESWITCH = 't',
	OBFUN    = 'x',
	OEFUN    = 'k',
};

enum builtins {
	BVA_START = 's',
	BVA_END   = 'e',
	BVA_ARG   = 'a',
	BVA_COPY  = 'c',
};

enum nerrors {
	EEOFFUN,       /* EOF while parsing function */
	ENLABEL,       /* label without statement */
	EIDOVER,       /* identifier overflow */
	EOUTPAR,       /* out pf params */
	ESYNTAX,       /* syntax error */
	ESTACKA,       /* stack unaligned */
	ESTACKO,       /* stack overflow */
	ESTACKU,       /* stack underflow */
	ELNLINE,       /* line too long */
	ELNBLNE,       /* line without new line */
	EFERROR,       /* error reading from file:%s */
	EBADID,        /* incorrect symbol id */
	EWTACKO,       /* switch stack overflow */
	EWTACKU,       /* switch stack underflow */
	ENOSWTC,       /* Out of switch statement */
	EBBUILT,       /* Unknown builtin */
	EOVERFL,       /* Numerical overflow */
	EBAFFUN,       /* Function body not finished */
	ENUMERR
};

typedef struct node Node;
typedef struct type Type;
typedef struct symbol Symbol;
typedef struct addr Addr;
typedef struct inst Inst;
typedef struct block Block;
typedef struct swtch Swtch;
typedef struct mach Mach;

struct mach {
	int swtchif;
};

struct swtch {
	int nr;
	long long min, max;
	Node *bswtch;
	Node *eswtch;
	Node **cases;
	Node *defnode;

	Swtch *next;
};

struct type {
	unsigned long size;
	unsigned align;
	unsigned short id;
	unsigned short flags;
};

struct symbol {
	Type type;
	Type rtype;
	unsigned short id;
	unsigned short numid;
	int refcnt;
	char *name;
	char kind;
	union {
		long off;
		Node *stmt;
		Inst *inst;
	} u;
	Symbol *next, *prev;
	Symbol *h_next;
};

struct node {
	char op;
	Type type;
	int complex;
	int address;
	unsigned flags;
	union {
		unsigned long long i;
		char *s;
		Symbol *sym;
		Swtch *swtch;
		int reg;
		int subop;
		long off;
	} u;
	Symbol *label;
	Block *bb;
	Node *left, *right;
	Node *next, *prev;
};

struct block {
	int id;
	int printed, visited;
	Node *entryp, *exitp;
	Block *true, *false;
	Swtch *swtch;
	Block *next;
};

struct addr {
	char kind;
	union {
		int reg;
		unsigned long long i;
		Symbol *sym;
		long off;
	} u;
};

struct inst {
	unsigned char op;
	unsigned char flags;
	Symbol *label;
	Inst *next, *prev;
	Addr from1, from2, to;
};

/* main.c */
void error(unsigned nerror, ...);

/* parse.c */
void parse(void);

/* cgen.c */
void genaddr(void);
void genasm(void);
Node *tsethi(Node *);

/* peep.c */
void peephole(void);

/* code.c */
void data(Node *np);
void writeout(void), endinit(void);
void code(int op, Node *to, Node *from1, Node *from2);
void defvar(Symbol *), defpar(Symbol *), defglobal(Symbol *);
void setlabel(Symbol *);
Node *label2node(Node *np, Symbol *sym);
Node *constnode(Node *np, unsigned long long n, Type *tp);
Node *tmpnode(Type *, Symbol *);
Node *idxnode(Node *, long);
void delcode(void);
Symbol *newlabel(void);
void pprint(char *s);
void deftype(Type *);
Node *labelstmt(Node *, Symbol *);
Node *keeplabel(void);

/* node.c */
void newfun(Symbol *, Node *);
void apply(Node *(*fun)(Node *));
void cleannodes(void);
void delnode(Node *np);
void deltree(Node *np);
void prtree(Node *np), prforest(char *msg);
Node *node(int op);
Node *addstmt(Node *);
Node *delstmt(Node *);
Node *insstmt(Node *, Node *);
Node *prestmt(Node *);
void delrange(Node *, Node *);
Node *unlinkstmt(Node *);

/* symbol.c */
#define TMPSYM  0
Symbol *getsym(unsigned id);
void popctx(void);
void pushctx(void);
void freesym(Symbol *sym);

/* cfg.c */
void gencfg(void);
void cleancfg(void);
Node *sethi(Node *);

/* swtch.c */
void cleanswtch(void);
Swtch *newswtch(Swtch *);
Node *swtch(Node *);
Node *swtchdefault(Swtch *);

/* globals */
extern Symbol *curfun;
extern Symbol *locals;
extern Inst *pc, *prog;
extern Node *laststmt;
extern Mach mach;

/* target */
extern Type int8type, int16type, int32type, int64type,
            uint8type, uint16type, uint32type, uint64type,
            float32type, float64type, float80type,
            booltype,
            ptrtype,
            voidtype,
            arg_type;
