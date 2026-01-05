/*
 * some systems define macros with this name even when
 * they should be c99 compliant.
 */
#undef LITTLE_ENDIAN
#undef BIG_ENDIAN

#define NBYTES 32
#define OBJ(format,arch,order) ((order) << 10 | (arch) << 5 | (format))
#define FORMAT(t) ((t) & 0x1f)
#define ARCH(t) (((t) >> 5) & 0x1f)
#define ORDER(t) (((t) >> 10) & 0x1f)
#define objfmt(o) FORMAT((o)->type)

typedef struct section Section;
typedef struct symbol Symbol;
typedef struct obj Obj;
typedef struct map Map;
typedef struct mapsec Mapsec;

enum objformat {
	COFF32,
	ELF,
	NFORMATS,
};

enum objarch {
	ARCH286,
	ARCH386,
	ARCHAMD64,
	ARCHZ80,
	ARCHARM32,
	ARCHARM64,
	ARCHUNK32,
	ARCHUNK64,
};

enum order {
	LITTLE_ENDIAN,
	BIG_ENDIAN,
};

/**
 * enum sectype - Section property flags
 * @SREAD: The segment has read rights
 * @SWRITE: The segment has write rights
 * @SEXEC: The segment has execution rights
 * @SLOAD: Segment data is loaded from disk to memory
 * @SALLOC: Segment is allocated in memory
 * @SRELOC: Segment has to be relocated
 * @SABS: Segment is loaded in a specific address
 */
enum sectype {
	SREAD   = 1 << 0,
	SWRITE  = 1 << 1,
	SEXEC   = 1 << 2,
	SLOAD   = 1 << 3,
	SALLOC  = 1 << 4,
	SRELOC  = 1 << 5,
	SABS    = 1 << 6,
};

enum symtype {
	SYMNOTYPE,
	SYMOBJECT,
	SYMFUNC,
	SYMSECTION,
	SYMFILE,
	SYMCOMMON,
};

struct ar_hdr;

struct obj {
	char *index;
	int type;
	long pos;
	void *data;
	Obj *next;
};

struct section {
	char *name;
	unsigned long long base;
	unsigned long long load;
	unsigned long long size;
	long offset;

	unsigned flags;
	int index;
	int align;
	int fill;
	char type;
};

#ifdef stdin
struct mapsec {
	Section sec;
	int used;
	int loaded;
	FILE *fp;
	long fsiz;

	int nchild;
	struct mapsec **child;
};
#endif

struct map {
	int nsec, nseg;
	struct mapsec *sec;
	struct mapsec *seg;
};

/**
 * @stype: Used internally by libmach
 * @dtype: Coff debug type
 * @flags: Used only by the assembler
 */
struct symbol {
	char *name;
	unsigned long long size;
	unsigned long long value;
	int index;
	int section;
	char type;
	int stype;
	int dtype;
	unsigned flags;
};

#ifdef stdin
int archive(FILE *);
long armember(FILE *, char *, struct ar_hdr *);

int objprobe(FILE *, char **);
int objpos(Obj *, FILE *, long);

int readobj(Obj *, FILE *);
int writeobj(Obj *, Map *, FILE *);

Map *loadmap(Obj *, FILE *);

int mapsec(Map *, Section *, FILE *, long);
int mapseg(Map *, Section *, FILE *, long);

int setindex(int, long, char **, long *, FILE *);
int getindex(int, long *, char ***, long **, FILE *);

#endif

Map *newmap(int, int);
Map *remap(Map *, int, int);
void delmap(Map *);

int objtype(char *);
Obj *newobj(int);
void delobj(Obj *);

int strip(Obj *);
int pc2line(Obj *, unsigned long long, char *, int *);
int rebase(Obj *, int, unsigned long long);

int findsec(Map *, char *);
int findseg(Map *, unsigned long long);

Symbol *getsym(Obj *, int *, Symbol *);
Symbol *setsym(Obj *, int *, Symbol *);
Section *getsec(Obj *, int *, Section *);
Section *setsec(Obj *, int *, Section *);
