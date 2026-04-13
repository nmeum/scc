#include <scc/scc.h>

#include "cc2.h"

static Node *
assignnode(Type *tp, Node *lhs, Node *rhs)
{
	Node *np;

	np = node(OASSIG);
	np->type = *tp;
	np->left = lhs;
	np->right = rhs;
	return sethi(np);
}

static Node *
branchnode(Node *cond, Symbol *sym)
{
	Node *np;
	int op = cond ? OBRANCH : OJMP;

	np = node(op);
	np->op = op;
	np->left = sethi(cond);
	np->u.sym = sym;
	sym->refcnt++;

	return np;
}

static Node *
boolean(Node *cond, Symbol *strue, Symbol *sfalse)
{
	Symbol *label;
	Node *p, *l = cond->left, *r = cond->right;

	switch (cond->op) {
	case ONEG:
		l = boolean(l, sfalse, strue);
		break;
	case OAND:
		label = newlabel();
		l = boolean(l, label, sfalse);
		prestmt(labelstmt(NULL, label));
		r = boolean(r, strue, sfalse);
		break;
	case OOR:
		label = newlabel();
		l = boolean(l, strue, label);
		prestmt(labelstmt(NULL, label));
		r = boolean(r, strue, sfalse);
		break;
	default:
		prestmt(branchnode(cond, strue));
		prestmt(branchnode(NULL, sfalse));
		return NULL;
	}

	cond->left = l;
	cond->right = r;
	return cond;
}

Node *
logicexpr(Node *np)
{
	Node *tmpvar, *p, *zero, *one;
	Type *tp = &np->type;
	Symbol *strue, *sfalse, *phi, *tmpsym;

	strue = newlabel();
	sfalse = newlabel();
	phi = newlabel();

	boolean(np, strue, sfalse);

	tmpvar = tmpnode(tp, NULL);
	tmpsym = tmpvar->u.sym;
	zero = constnode(NULL, 0, tp);
	one = constnode(NULL, 1, tp);

	p = assignnode(tp, tmpnode(tp, tmpsym), one);
	prestmt(labelstmt(p, strue));

	prestmt(branchnode(NULL, phi));

	p = assignnode(tp, tmpnode(tp, tmpsym), zero);
	prestmt(labelstmt(p, sfalse));

	prestmt(labelstmt(NULL, phi));

	return sethi(tmpvar);
}

static void
comma(Node *np)
{
	if (np->op != OCOMMA) {
		prestmt(sethi(np));
	} else {
		comma(np->left);
		prestmt(sethi(np->right));
		delnode(np);
	}
}

static Node *
ternary(Node *np)
{
	Type *tp;
	Node *tmpvar, *colon, *p;
	Symbol *tmpsym, *strue, *sfalse, *phi;

	strue = newlabel();
	sfalse = newlabel();
	phi = newlabel();
	boolean(np->left, strue, sfalse);

	tp = &np->type;
	colon = np->right;
	tmpvar = tmpnode(tp, NULL);
	tmpsym = tmpvar->u.sym;

	prestmt(labelstmt(NULL, strue));
	p = assignnode(tp, tmpnode(tp, tmpsym), sethi(colon->left));
	prestmt(p);
	prestmt(branchnode(NULL, phi));

	prestmt(labelstmt(NULL, sfalse));
	p = assignnode(tp, tmpnode(tp, tmpsym), sethi(colon->right));
	prestmt(p);

	prestmt(labelstmt(NULL, phi));

	return sethi(tmpvar);
}

static Node *
replace(Node *what, Node *with)
{
	Node *prev, *next;
	Symbol *label;

	label = what->label;
	next = what->next, prev = what->prev;

	*what = *with;
	delnode(with);
	what->next = next, what->prev = prev;
	what->label = label;

	return sethi(what);
}

Node *
sethi(Node *np)
{
	int op;
	Node *next, *l, *r;

	if (!np)
		return np;

	np->complex = 0;
	np->address = 0;

	switch (np->op) {
	case OBSWITCH:
		np = swtch(np);
		break;
	case OBRANCH:
		next = np->next;
		if (!next->label)
			labelstmt(next, NULL);

		op = np->left->op;
		if (op != ONEG && op != OOR && op != OAND) {
			sethi(np->left);
			return np;
		}

		boolean(np->left, np->u.sym, next->label);
		np->u.sym->refcnt--;
		return NULL;
	case OCOMMA:
		r = np->right;
		comma(np->left);
		return replace(np, r);
	case OASK:
		return replace(np, ternary(np));
	case ONEG:
	case OAND:
	case OOR:
		return replace(np, logicexpr(np));
	default:
		np = tsethi(np);
		break;
	}

	l = np->left;
	r = np->right;

	if (np->address > 10)
		return np;
	if (l)
		np->complex = l->complex;
	if (r) {
		int d = np->complex - r->complex;

		if (d == 0)
			++np->complex;
		else if (d < 0)
			np->complex = r->complex;
	}
	if (np->complex == 0)
		++np->complex;

	return np;
}

static Node *
presethi(Node *np)
{
	/* just in case ... */
	savelabel();
	return sethi(np);
}

void
genaddr(void)
{
	apply(presethi);
	PRTREE("after sethi");
}
