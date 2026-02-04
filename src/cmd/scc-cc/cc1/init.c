#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <scc/cstd.h>
#include <scc/scc.h>
#include "cc1.h"

#define NOLIST 0
#define INLIST 1


typedef struct init Init;

struct designator {
	long long pos;
	Node *expr;
	struct designator *next;
};

struct init {
	unsigned long long pos;
	unsigned long long max;
	struct designator *tail;
	struct designator *head;
};

int disstring;

static long long
arydesig(Type *tp, Init *ip)
{
	long long npos;
	Node *np;

	if (tp->op != ARY)
		errorp("array index in non-array initializer");
	next();
	np = constexpr();
	npos = np->sym->u.i;
	if (npos < 0 || (tp->prop & TDEFINED) && npos >= tp->n.elem) {
		errorp("array index in initializer exceeds array bounds");
		npos = 0;
	}
	freetree(np);
	expect(']');
	return npos;
}

static long long
fielddesig(Type *tp, Init *ip)
{
	int ons;
	Symbol *sym, **p;

	if (!(tp->prop & TAGGREG))
		errorp("field name not in record or union initializer");
	ons = namespace;
	namespace = tp->ns;
	next();
	namespace = ons;
	if (yytoken != IDEN)
		unexpected();
	sym = yylval.sym;
	next();
	if ((sym->flags & SDECLARED) == 0) {
		errorp("unknown field '%s' specified in initializer",
		      sym->name);
		return -1;
	}
	for (p = tp->p.fields; *p != sym; ++p)
		;
	return p - tp->p.fields;
}

static Init *
init(Init *ip)
{
	ip->tail = ip->head = NULL;
	ip->pos = ip->max = 0;
	return ip;
}

static Node *
str2ary(Type *tp)
{
	Node *np;
	Type *btp = tp->type;
	Symbol *sym;
	long long i, olen, len;
	char *s;

	disstring = 1;
	np = assign();
	disstring = 0;
	sym = np->left->sym;
	if (btp != chartype && btp != uchartype && btp != schartype) {
		errorp("array of inappropriate type initialized from string constant");
		return constnode(zero);
	}

	len = tp->n.elem;
	olen = sym->type->n.elem-1;
	if (!(tp->prop & TDEFINED)) {
		len = tp->n.elem = olen+1;
		deftype(tp);
	} else if (len < olen) {
		warn("initializer-string for array of chars is too long");
	}

	s = sym->u.s;
	sym = newstring(NULL, len);
	for (i = 0; i < len; i++)
		sym->u.s[i] = (i < olen) ? *s++ : '\0';

	assert(np->op == OADDR);
	np->left->sym = sym;
	np->left->type = sym->type;
	np->sym = sym;
	np->type = sym->type;

	return np;
}

static Node *
initialize(Type *tp, int inlist)
{
	Node *np;
	Symbol *sym;

	if (tp->op == ARY && yytoken == STRING)
		return str2ary(tp);

	if (yytoken == '{' || inlist && (tp->op == STRUCT || tp->op == ARY))
		return initlist(tp);

	np = assign();
	if (!eqtype(tp, np->type, EQUIV)) {
		np = convert(decay(np), tp, 0);
		if (!np) {
			errorp("incorrect initializer");
			return constnode(zero);
		}
	}

	return simplify(np);
}

static Node *
mkcompound(Init *ip, Type *tp)
{
	Node **v, **p, *np;
	size_t n;
	struct designator *dp, *next;
	Symbol *sym;
	int isconst = 1;

	if (tp->op == UNION) {
		np = NULL;
		v = xmalloc(sizeof(*v));
		for (dp = ip->head; dp; dp = next) {
			freetree(np);
			np = dp->expr;
			next = dp->next;
			free(dp);
		}
		if ((np->flags & NCONST) == 0)
			isconst = 0;
		*v = np;
	} else {
		n = (tp->prop&TDEFINED) ? tp->n.elem : ip->max;
		if (n == 0) {
			v = NULL;
		} else if (n > SIZE_MAX / sizeof(*v)) {
			errorp("compound literal too big");
			return constnode(zero);
		} else {
			n *= sizeof(*v);
			v = memset(xmalloc(n), 0, n);

			for (dp = ip->head; dp; dp = next) {
				p = &v[dp->pos];
				freetree(*p);
				np = dp->expr;
				*p = np;
				if ((np->flags & NCONST) == 0)
					isconst = 0;
				next = dp->next;
				free(dp);
			}
		}
	}

	sym = newsym(NS_IDEN, NULL);
	sym->u.init = v;
	sym->type = tp;
	sym->flags |= SINITLST;

	return (isconst ? constnode : varnode)(sym);
}

static void
newdesig(Init *ip, Node *np)
{
	struct designator *dp;

	dp = xmalloc(sizeof(*dp));
	dp->pos = ip->pos;
	dp->expr = np;
	dp->next = NULL;

	if (ip->head == NULL) {
		ip->head = ip->tail = dp;
	} else {
		ip->tail->next = dp;
		ip->tail = dp;
	}

	if (ip->pos+1 > ip->max)
		ip->max = ip->pos+1;
}

static Node *
initlist_helper(Type *tp)
{
	Init in;
	Node *np;
	Type *curtp;
	int braces, scalar, toomany, outbound;
	long long nelem = tp->n.elem;

	init(&in);
	braces = scalar = toomany = 0;

	if (accept('{'))
		braces = 1;

	for (;;) {
		curtp = inttype;
		switch (yytoken) {
		case '[':
			in.pos = arydesig(tp, &in);
			curtp = tp->type;
			goto desig_list;
		case '.':
			in.pos = fielddesig(tp, &in);
			if (in.pos >= 0 && in.pos < nelem)
				curtp = tp->p.fields[in.pos]->type;
		desig_list:
			if (yytoken == '[' || yytoken == '.') {
				np = initlist(curtp);
				goto new_desig;
			}
			expect('=');
		default:
			outbound = 0;

			switch (tp->op) {
			case ARY:
				curtp = tp->type;
				if (!(tp->prop & TDEFINED) || in.pos < tp->n.elem)
					break;
				if (!toomany)
					warn("excess elements in array initializer");
				toomany = 1;
				outbound = 1;
				break;
			case UNION:
			case STRUCT:
				if (in.pos < nelem) {
					curtp = tp->p.fields[in.pos]->type;
					break;
				}
				if (!toomany)
					warn("excess elements in struct initializer");
				toomany = 1;
				outbound = 1;
				break;
			default:
				curtp = tp;
				if (!scalar)
					warn("braces around scalar initializer");
				scalar = 1;
				if (in.pos == 0)
					break;
				if (!toomany)
					warn("excess elements in scalar initializer");
				toomany = 1;
				outbound = 1;
				break;
			}
			np = initialize(curtp, INLIST);
			if (outbound) {
				freetree(np);
				np = NULL;
			}
		}

new_desig:
		if (np)
			newdesig(&in, np);
		if (++in.pos == 0)
			errorp("compound literal too big");
		if (nelem == in.pos && !braces)
			break;
		if (!accept(','))
			break;
		if (yytoken == '}')
			break;
	}

	if (braces)
		expect('}');


	if (tp->op == ARY && !(tp->prop & TDEFINED)) {
		tp->n.elem = in.max;
		deftype(tp);
	}
	if (in.max == 0) {
		errorp("empty braced initializer");
		return constnode(zero);
	}

	return mkcompound(&in, tp);
}

Node *
initlist(Type *tp)
{
	Node *np;
	static int depth;

	if (depth == NR_SUBTYPE)
		error("too many nested initializers");

	++depth;
	np = initlist_helper(tp);
	--depth;

	return np;
}

static void
emitstrings(Node *np)
{
	unsigned f;
	Symbol *sym;

	if (!np)
		return;

	if (np->op == OSYM) {
		sym = np->sym;
		f = sym->flags & (SSTRING|SEMITTED);
		if (f == SSTRING) {
			emit(ODECL, sym);
			emit(OINIT, constnode(sym));
		}
	}

	emitstrings(np->left);
	emitstrings(np->right);
}

static void
autoinit(Symbol *sym, Node *np)
{
	Symbol *hidden;
	Type *tp = sym->type;

repeat:
	switch (tp->op) {
	case UNION:
		np = np->sym->u.init[0];
		tp = np->type;
		goto repeat;
	case ARY:
		if (np->op == OADDR && np->sym->flags & SSTRING)
			goto hidden_data;
	case STRUCT:
		if (np->op != OSYM || (np->sym->flags & SINITLST) == 0)
			goto expr;
	hidden_data:
		if (!(np->flags & NCONST))
			abort(); /* TODO */
		hidden = newsym(NS_IDEN, NULL);
		hidden->id = newid();
		hidden->type = sym->type;
		hidden->flags |= SLOCAL | SHASINIT;
		emit(ODECL, hidden);
		emit(OINIT, np);
		np = varnode(hidden);
	default:
	expr:
		emitstrings(np);
		emit(ODECL, sym);
		np = node(OASSIGN, tp, varnode(sym), np);
		emit(OEXPR, np);
		break;
	}
}

void
initializer(Symbol *sym, Type *tp)
{
	Node *np;
	int flags = sym->flags;

	if (tp->op == FTN) {
		errorp("function '%s' initialized like a variable",
		       sym->name);
		tp = inttype;
	}
	np = initialize(tp, NOLIST);

	if (flags & SDEFINED) {
		errorp("redeclaration of '%s'", sym->name);
	} else if ((flags & (SGLOBAL|SLOCAL|SPRIVATE)) != 0) {
		if ((np->flags & NCONST) == 0) {
			errorp("initializer element is not constant");
			return;
		}
		sym->flags |= SHASINIT;
		sym->flags &= ~SEMITTED;
		emit(ODECL, sym);
		emit(OINIT, np);
		sym->flags |= SDEFINED;
	} else if ((flags & (SEXTERN|STYPEDEF)) != 0) {
		errorp("'%s' has both '%s' and initializer",
		       sym->name, (flags&SEXTERN) ? "extern" : "typedef");
	} else {
		autoinit(sym, np);
	}
}
