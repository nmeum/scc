#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <scc/cstd.h>
#include <scc/scc.h>
#include "cc1.h"

struct ifstate {
	unsigned char done;
	unsigned char enabled;
	unsigned char iselse;
};

static unsigned ncmdlines;
static Symbol *symline, *symfile;
static struct ifstate ifstate[NR_COND];
static int cppoff;
static struct items dirinclude;

unsigned cppctx;
int disexpand;
int disescape;

void
defdefine(char *name, char *val, char *source)
{
	char buffer[INPUTSIZ+1];
	char *def, *fmt = "#define %s %s\n";
	Symbol *sym = &(Symbol) {
		.name = name,
		.flags = SDECLARED,
	};

	if (!val)
		val = "";
	if (strlen(fmt) + strlen(name) + strlen(val) > INPUTSIZ) {
		errorp("macro definition '%s' too big", name);
		return;
	}

	sprintf(buffer, fmt, name, val);
	lineno = ++ncmdlines;

	addinput(IPARAM, buffer, FAIL);
	cpp();
	delinput();
}

void
undefmacro(char *s)
{
	killsym(lookup(NS_CPP, s, NOALLOC));
}

void
icpp(void)
{
	struct tm *tm;
	time_t t;
	static char sdate[14], stime[11];
	static struct {
		char *name;
		char *value;
	} *bp, list[] = {
		{"__STDC__", "1"},
		{"__STDC_HOSTED__", "1"},
		{"__SCC__", "1"},
		{"__DATE__", sdate},
		{"__TIME__", stime},
		{"__STDC_VERSION__", STDC_VERSION},
		{"__LINE__", NULL},
		{"__FILE__", NULL},
		{"__FLT_EVAL_METHOD__", 0},
		{NULL, NULL}
	};

	t = time(NULL);
	tm = localtime(&t);
	strftime(sdate, sizeof(sdate), "\"%b %d %Y\"", tm);
	strftime(stime, sizeof(stime), "\"%H:%M:%S\"", tm);

	for (bp = list; bp->name; ++bp)
		defdefine(bp->name, bp->value, "built-in");

	symline = lookup(NS_CPP, "__LINE__", ALLOC);
	symfile = lookup(NS_CPP, "__FILE__", ALLOC);

	ncmdlines = 0;
}

static void
nextcpp(Macro *mp)
{
	int len, siz;
	char *arg;

	next();
	if (yytoken == EOFTOK) {
		error("unterminated argument list invoking macro \"%s\"",
		      mp->sym->name);
	}

	if (yytoken == IDEN)
		yylval.sym->flags |= SUSED;

	len = strlen(yytext);
	siz = mp->argsiz;
	if (len+1 > INT_MAX - siz) {
		error("too long argument invoking macro \"%s\"",
		      mp->sym->name);
	}

	arg = xrealloc(mp->arg, siz + len + 1);
	if (siz > 0) {
		arg[siz-1] = ' ';
		memcpy(arg + siz, yytext, len+1);
	} else {
		memcpy(arg, yytext, len+1);
	}

	mp->arg = arg;
	mp->argsiz = siz + len + 1;
}

static void
paren(Macro *mp)
{
	for (;;) {
		nextcpp(mp);
		switch (yytoken) {
		case ')':
			return;
		case '(':
			paren(mp);
			break;
		}
	}
}

static char *
parameter(Macro *mp)
{
	int siz;
	char *s, *begin, *end;
	Input *ip = input;

	mp->arg = NULL;
	mp->argsiz = 0;
	for (;;) {
		nextcpp(mp);
		switch (yytoken) {
		case ')':
		case ',':
			/* remove ","  or ")"*/
			begin = mp->arg;
			end = mp->arg + mp->argsiz - 2;

			while (end > begin && isspace(end[-1]))
				--end;
			while (begin < end && isspace(begin[0]))
				++begin;

			siz = end - begin;
			s = memcpy(xmalloc(siz+1), begin, siz);
			s[siz] = '\0';
			free(mp->arg);

			return s;
		case '(':
			paren(mp);
			break;
		}
	}
}

static int
parsepars(Macro *mp)
{
	int n;

	if (mp->npars == -1)
		return 1;
	if (ahead() != '(')
		return 0;

	disexpand = 1;
	next();
	n = 0;

	if (mp->npars == 0 && ahead() == ')') {
		next();
	} else {
		do {
			mp->arglist = xrealloc(mp->arglist, (n+1)*sizeof(char *));
			mp->arglist[n] = parameter(mp);
			DBG("MACRO fetched arg '%s'", mp->arglist[n]);
		} while (++n < NR_MACROARG && yytoken == ',');
	}

	if (yytoken != ')')
		error("incorrect macro function-alike invocation");
	disexpand = 0;

	if (n == NR_MACROARG)
		error("too many parameters in macro \"%s\"", mp->sym->name);
	if (n != mp->npars) {
		error("macro \"%s\" received %d arguments, but it takes %d",
		      mp->sym->name, n, mp->npars);
	}

	return 1;
}

static int
concatoper(char *def, char *cur)
{
	char *s;

	for (s = cur + 4; isspace(*s); ++s)
		;
	if (*s == CONCAT)
		return 1;

	for (s = cur; s > def && isspace(s[-1]); --s)
		;
	if (s > def && s[-1] == CONCAT)
		return 1;

	return 0;
}

static int
expandarg(char *arg, char *def, char *curdef, char *buf, int bufsiz)
{
	int siz;
	char *s = buf;

	/* gives priority to concatenation operators */
	if (concatoper(def, curdef)) {
		siz = strlen(arg);
		if (siz >= bufsiz) {
			siz = -1;
		} else {
			memcpy(buf, arg, siz);
			buf += siz;
		}
	} else {
		addinput(IPARAM, arg, FAIL);
		for (siz = 0; next() != EOFTOK; siz += yylen+1) {
			if (yylen > bufsiz-2) {
				siz = -1;
				break;
			}
			memcpy(buf, yytext, yylen);
			bufsiz -= yylen + 1;
			buf += yylen;
			*buf++ = ' ';
		}

		delinput();
	}
	*buf = '\0';

	DBG("MACRO parameter '%s' expanded to '%s'", arg, s);

	return siz;
}

static int
copymacro(Macro *mp)
{
	int delim, c, esc;
	char *s, *p, *arg, *bp;
	int size, bufsiz;

	if (mp->sym == symfile)
		return sprintf(mp->buffer, "\"%s\" ", filenam);
	if (mp->sym == symline)
		return sprintf(mp->buffer, "%d ", lineno);

	bp = mp->buffer;
	bufsiz = mp->bufsiz;
	for (s = mp->def; c = *s; ++s) {
		switch (c) {
		case '\'':
			delim = '\'';
			goto search_delim;
		case '\"':
			delim = '"';
		search_delim:
			esc = 0;
			p = s;
			for (++s; c = *s; ++s) {
				if (c == '\\' && !esc)
					esc = 1;
				else if (c == delim &&!esc)
					break;
				else
					esc = 0;
			}
			size = s - p + 1;
			if (size > bufsiz)
				goto expansion_too_long;
			memcpy(bp, p, size);
			bufsiz -= size;
			bp += size;
			break;
		case CONCAT:
			/* token concatenation operator */
			DBG("MACRO concat");
			while (bp[-1] == ' ')
				--bp, ++bufsiz;
			while (s[1] == ' ')
				++s;
			break;
		case STRINGIZE:
			/* stringfier operator */
			DBG("MACRO stringize");
			arg = mp->arglist[atoi(s += 2)];
			s += 2;

			if (bufsiz < 3)
				goto expansion_too_long;

			*bp++ = '"';
			while ((c = *arg++) != '\0') {
				if (c == '"') {
					if (bufsiz < 3)
						goto expansion_too_long;
					*bp++ = '\\';
					*bp++ = '"';
					bufsiz -= 2;
				} else {
					if (bufsiz < 2)
						goto expansion_too_long;
					*bp++ = c;
					bufsiz--;
				}
			}
			*bp++ = '"';

			break;
		case MACROPAR:
			/* parameter substitution */
			arg = mp->arglist[atoi(s+1)];
			size = expandarg(arg, mp->def, s, bp, bufsiz);
			if (size < 0)
				goto expansion_too_long;
			bp += size;
			bufsiz -= size;
			s += 3;
			break;
		default:
			if (bufsiz-- == 0)
				goto expansion_too_long;
			*bp++ = c;
			break;
		}
	}
	*bp = '\0';

	return bp - mp->buffer;

expansion_too_long:
	error("macro expansion of \"%s\" too long", mp->sym->name);
}

static void
addhideset(Input *ip,  Symbol *sym)
{
	Symbol **set;
	Symbol **p;

	set = ip->macro->hideset;
	for (p = set; p < &set[NR_MACROARG] && *p; ++p) {
		if (*p == sym)
			return;
	}

	if (p == &set[NR_MACROARG])
		error("too complex macro expansion");

	*p = sym;
	DBG("MACRO Adding %s to hideset of %s",
	    sym->name, ip->macro->sym->name);
}

static void
hide(Symbol *sym)
{
	DBG("SYM: hidding symbol %s %d", sym->name, sym->hide);
	sym->hide = 1;
}

static void
unhide(Symbol *sym)
{
	DBG("SYM: unhidding symbol %s %d", sym->name, sym->hide);
	sym->hide = 0;
}

void
delmacro(Macro *mp)
{
	int i;
	Symbol **p;

	if (!mp)
		return;

	if (mp->arglist) {
		for (i = 0; i < mp->npars; i++)
			free(mp->arglist[i]);
	}

	for (p = mp->hideset; p < &mp->hideset[NR_MACROARG] && *p; ++p)
		unhide(*p);

	free(mp->arglist);
	free(mp);
}

Macro *
newmacro(Symbol *sym)
{
	Macro *mp;

	mp = xmalloc(sizeof(*mp));
	*mp = (Macro) {0};
	mp->sym = sym;
	mp->def = sym->u.s + 3;
	if (sym->u.s)
		mp->npars = atoi(sym->u.s);

	return mp;
}

int
expand(Symbol *sym)
{
	int siz;
	Macro *mp;
	Input *ip;
	Symbol **p;

	DBG("MACRO '%s' detected disexpand=%d hide=%d",
	    sym->name, disexpand, sym->hide);

	if (disexpand || sym->hide || sym->token != IDEN)
		return 0;

	mp = newmacro(sym);
	mp->fname = filenam;

	if (!parsepars(mp)) {
		delmacro(mp);
		return 0;
	}

	addinput(IMACRO, mp, FAIL);
	mp->buffer = input->line;
	mp->bufsiz = INPUTSIZ-1;

	siz = copymacro(mp);
	mp->buffer[siz] = '\0';

	for (ip = input; ip; ip = ip->next) {
                if ((ip->flags & ITYPE) == IMACRO)
			addhideset(ip, sym);
	}

	for (p = mp->hideset; p < &mp->hideset[NR_MACROARG] && *p; ++p)
		hide(*p);

	DBG("MACRO '%s' expanded to :'%s'", mp->sym->name, mp->buffer);

	return 1;
}

static int
getpars(Symbol *args[NR_MACROARG])
{
	int n, c;
	Symbol *sym;

	if (*input->p != '(')
		return -1;

	/* skip the '(' */
	next();
	next();
	if (yytoken == ')')
		return 0;

	n = 0;
	do {
		if (n == NR_MACROARG) {
			cpperror("too many parameters in macro");
			return NR_MACROARG;
		}
		if (accept(ELLIPSIS)) {
			args[n++] = NULL;
			break;
		}
		if (yytoken != IDEN) {
			cpperror("macro arguments must be identifiers");
			return NR_MACROARG;
		}
		if ((sym = install(NS_IDEN, yylval.sym)) == NULL) {
			errorp("duplicated macro parameter '%s'", yytext);
		} else {
			sym->flags |= SUSED;
			args[n++] = sym;
		}
		next();
	} while (accept(','));

	if (yytoken != ')') {
		cpperror("expected ')' at the end of macro argument list");
		return NR_MACROARG;
	}

	return n;
}

static int
getdefs(Symbol *args[NR_MACROARG], int nargs, char *buffer, size_t bufsiz)
{
	size_t len;
	char *bp, *p;
	Symbol **argp, *sym;
	int c, id, token, prevc, ispar;

	while (isspace(*input->p))
		++input->p;

	bp = buffer;
	for (prevc = 0; (c = *input->p) != '\n' && c != '\0'; ++input->p) {
		len = 1;
		ispar = 0;
		token = c;
		sym = NULL;

		if (c == '#') {
			if (input->p[1] == '#') {
				token = CONCAT;
				++input->p;
			} else {
				token = STRINGIZE;
			}
		} else if (c == '_' || isalpha(c)) {
			token = IDEN;
			for (p = input->p; isalnum(*p) || *p == '_'; ++p)
				;
			len = p - input->p;
			if (len >  INTIDENTSIZ) {
				cpperror("identifier too long in macro definition");
				return 0;
			}
			memcpy(yytext, input->p, len);
			yytext[len] = '\0';
			yylen = len;
			input->p = p - 1;
			sym = lookup(NS_IDEN, yytext, NOALLOC);
		} else if (c == '"') {
			next();
			assert(yytoken == STRING);
			token = STRING;
			len = yylen;
		}

		if (sym && nargs > 0) {
			for (argp = args; argp < &args[nargs]; ++argp) {
				if (*argp == sym)
					break;
			}
			if (argp != &args[nargs]) {
				id = argp - args;
				sprintf(yytext,
					"%c%02d%c", MACROPAR, id, MACROPAR);
				ispar = 1;
				yylen = len = 4;
			}
		}

		if (prevc == 0 && token == CONCAT)
			goto wrong_concat;

		if (prevc == STRINGIZE && !ispar) {
			cpperror("'#' is not followed by a macro parameter");
			return 0;
		}

		if (len >= bufsiz) {
			cpperror("macro too long");
			return 0;
		}

		if (token == IDEN || token == STRING)
			memcpy(bp, yytext, yylen);
		else
			*bp = token;

		bp += len;
		bufsiz -= len;
		prevc = token;
	}

end_loop:
	if ((yytoken = c) == '\0')
		yytoken = EOFTOK;
	if (prevc == CONCAT)
		goto wrong_concat;
	for ( ; bp > buffer && isspace(bp[-1]); --bp);
		;
	*bp = '\0';
	return 1;

wrong_concat:
	cpperror("'##' cannot appear at either ends of a macro expansion");
	return 0;
}

static void
define(void)
{
	Symbol *sym,*args[NR_MACROARG];
	char buff[LINESIZ+1];
	int n;

	if (cppoff)
		return;

	disescape = 1;
	namespace = NS_CPP;
	next();

	if (yytoken != IDEN) {
		cpperror("macro names must be identifiers");
		return;
	}
	sym = yylval.sym;
	if (sym->flags & SDECLARED) {
		warn("'%s' redefined", yytext);
		free(sym->u.s);
	} else {
		sym = install(NS_CPP, sym);
		sym->flags |= SDECLARED|SSTRING;
	}

	namespace = NS_IDEN;       /* Avoid polution in NS_CPP */
	if ((n = getpars(args)) == NR_MACROARG)
		goto delete;
	if (n > 0 && !args[n-1])  /* it is a variadic function */
		--n;

	sprintf(buff, "%02d#", n);
	if (!getdefs(args, n, buff+3, LINESIZ-3))
		goto delete;
	sym->u.s = xstrdup(buff);
	DBG("MACRO '%s' defined as '%s'", sym->name, buff);
	return;

delete:
	killsym(sym);
}

void
incdir(char *dir)
{
	if (!dir || *dir == '\0')
		die("cc1: incorrect -I flag");
	newitem(&dirinclude, dir);
}

static int
includefile(char *dir, char *file, size_t filelen)
{
	size_t dirlen;
	char path[FILENAME_MAX];

	if (!dir) {
		dirlen = 0;
		if (filelen > FILENAME_MAX-1)
			return 0;
	} else {
		dirlen = strlen(dir);
		if (dirlen + filelen > FILENAME_MAX-2)
			return 0;
		memcpy(path, dir, dirlen);
		if (dir[dirlen-1] != '/')
			path[dirlen++] = '/';
	}
	memcpy(path+dirlen, file, filelen);
	path[dirlen + filelen] = '\0';

	return addinput(IFILE, path, NOFAIL);
}

static char *
cwd(char *buf)
{
	char *p, *s = filenam;
	size_t len;

	if ((p = strrchr(s, '/')) == NULL)
		return NULL;
	if ((len = p - s) >= FILENAME_MAX)
		die("cc1: current work directory too long");
	memcpy(buf, s, len);
	buf[len] = '\0';
	return buf;
}

static void
include(void)
{
	char dir[FILENAME_MAX], file[FILENAME_MAX], *p, **bp;
	size_t filelen;
	int n;

	if (cppoff)
		return;

	disexpand = 0;
	namespace = NS_IDEN;
	next();

	switch (*yytext) {
	case '<':
		if ((p = strchr(input->begin, '>')) == NULL || p[-1] == '<')
			goto bad_include;
		filelen = p - input->begin;
		if (filelen >= FILENAME_MAX)
			goto too_long;
		memcpy(file, input->begin, filelen);
		file[filelen] = '\0';

		input->begin = input->p = p+1;
		if (next() != '\n')
			goto trailing_characters;

		break;
	case '"':
		if (yylen < 3)
			goto bad_include;
		filelen = yylen-2;
		if (filelen >= FILENAME_MAX)
			goto too_long;
		memcpy(file, yytext+1, filelen);
		file[filelen] = '\0';

		if (next() != '\n')
			goto trailing_characters;

		if (includefile(cwd(dir), file, filelen))
			goto its_done;
		break;
	default:
		goto bad_include;
	}

	n = dirinclude.n;
	for (bp = dirinclude.s; n--; ++bp) {
		if (includefile(*bp, file, filelen))
			goto its_done;
	}
	cpperror("included file '%s' not found", file);

its_done:
	return;

trailing_characters:
	cpperror("trailing characters after preprocessor directive");
	return;

too_long:
	cpperror("too long file name in #include");
	return;

bad_include:
	cpperror("#include expects \"FILENAME\" or <FILENAME>");
	return;
}

static void
line(void)
{
	long n;
	char *endp, *fname;

	if (cppoff)
		return;

	disexpand = 0;
	next();
	n = strtol(yytext, &endp, 10);
	if (n <= 0 || n > USHRT_MAX || *endp != '\0') {
		cpperror("first parameter of #line is not a positive integer");
		return;
	}

	next();
	if (yytoken == '\n') {
		fname = NULL;
	} else {
		if (*yytext != '\"' || yylen == 1) {
			cpperror("second parameter of #line is not a valid filename");
			return;
		}
		fname = yylval.sym->u.s;
	}
	setloc(fname, n - 1);
	if (yytoken != '\n')
		next();
}

static void
pragma(void)
{
	if (cppoff)
		return;
	next();
	warn("ignoring pragma '%s'", yytext);
	*input->p = '\0';
	next();
}

static void
usererr(void)
{
	if (cppoff)
		return;
	cpperror("#error %s", input->p);
	exit(EXIT_FAILURE);
	next();
}


Node *
defined(void)
{
	Symbol *sym;
	int paren;

	disexpand = 1;
	next();
	paren = accept('(');
	if (yytoken != IDEN && yytoken != TYPEIDEN)
		cpperror("operator 'defined' requires an identifier");
	if (yytoken == TYPEIDEN || !(yylval.sym->flags & SDECLARED))
		sym = zero;
	else
		sym = one;
	disexpand = 0;
	next();
	if (paren)
		expect(')');
	return constnode(sym);
}

static void
ifclause(int negate, int isifdef)
{
	Symbol *sym;
	unsigned n;
	int enabled, done;
	Node *expr;

	if (cppctx == NR_COND-1)
		error("too many nesting levels of conditional inclusion");
	n = cppctx++;
	DBG("CPP ifclause updates cppctx=%d", cppctx);

	if (n > 0 && !ifstate[n-1].enabled) {
		done = 1;
		enabled = 0;
		goto disabled;
	}

	namespace = NS_CPP;
	next();

	if (isifdef) {
		if (yytoken != IDEN) {
			cpperror("no macro name given in #%s directive",
			         (negate) ? "ifndef" : "ifdef");
			return;
		}
		sym = yylval.sym;
		next();
		enabled = (sym->flags & SDECLARED) != 0;
		if (!enabled)
			killsym(sym);
	} else {
		/* TODO: catch recovery here */
		if ((expr = constexpr()) == NULL) {
			cpperror("parameter of #if is not an integer constant expression");
			return;
		}
		DBG("CPP if expr=%d", expr->sym->u.i);
		enabled = expr->sym->u.i != 0;
		freetree(expr);
	}

	if (negate)
		enabled = !enabled;
	done = enabled;

disabled:
	cppoff = !enabled;
	DBG("CPP if result=%d", enabled);
	ifstate[n].done = done;
	ifstate[n].enabled = enabled;
	ifstate[n].iselse = 0;
}

static void
cppif(void)
{
	DBG("CPP line=%u if cppctx=%d", lineno, cppctx);
	disexpand = 0;
	ifclause(0, 0);
}

static void
ifdef(void)
{
	DBG("CPP line=%u ifdef cppctx=%d", lineno, cppctx);
	ifclause(0, 1);
}

static void
ifndef(void)
{
	DBG("CPP line=%u ifndef cppctx=%d", lineno, cppctx);
	ifclause(1, 1);
}

static void
cppelse(void)
{
	DBG("CPP line=%u else cppctx=%d", lineno, cppctx);

	if (cppctx == 0 || ifstate[cppctx-1].iselse) {
		cpperror("#else without #ifdef/ifndef");
		return;
	}

	/*
	 * If we are disabled by a upper ifdef then ifclause() already
	 * marked us as disabled and done. So if we are done then we
	 * disable cpp because or ifclause was true, or it was disabled
	 * by the upper. If we are not done, then it is our turn.
	 */
	if (ifstate[cppctx-1].done) {
		ifstate[cppctx-1].enabled = 0;
		cppoff = 1;
	} else {
		ifstate[cppctx-1].done = 1;
		ifstate[cppctx-1].enabled = 1;
		cppoff = 0;
	}

	next();
}

static void
elif(void)
{
	DBG("CPP line=%u elif cppctx=%d", lineno, cppctx);

	if (cppctx == 0 || ifstate[cppctx-1].iselse) {
		cpperror("#elif without #ifdef/ifndef");
		return;
	}

	/*
	 * If we are disabled by a upper ifdef then ifclause() already
	 * marked us as disabled and done. So if we are done then we
	 * disable cpp because or ifclause was true, or it was disabled
	 * by the upper. If we are not done, then we have to evaluate
	 * the if condition.
	 */
	if (ifstate[cppctx-1].done) {
		ifstate[cppctx-1].enabled = 0;
		cppoff = 1;
	} else {
		--cppctx;
		DBG("elif updates cppctx=%d", cppctx);
		cppif();
	}
}

static void
endif(void)
{
	DBG("CPP line=%u endif cppctx=%d", lineno, cppctx);

	if (cppctx == 0)
		error("#endif without #if");

	if (cppctx > 1)
		cppoff = !ifstate[cppctx - 2].enabled;
	else
		cppoff = 0;

	--cppctx;
	DBG("CPP endif updates cppctx=%d", cppctx);
	next();
}

static void
undef(void)
{
	if (cppoff)
		return;

	namespace = NS_CPP;
	next();
	if (yytoken != IDEN) {
		error("no macro name given in #undef directive");
		return;
	}
	killsym(yylval.sym);
	next();
}

int
cpp(void)
{
	static struct {
		unsigned char token;
		void (*fun)(void);
	} *bp, clauses [] = {
		{DEFINE, define},
		{INCLUDE, include},
		{LINE, line},
		{IFDEF, ifdef},
		{IF, cppif},
		{ELIF, elif},
		{IFNDEF, ifndef},
		{ELSE, cppelse},
		{ENDIF, endif},
		{UNDEF, undef},
		{PRAGMA, pragma},
		{ERROR, usererr},
		{0, NULL}
	};
	int ns;
	char *p;

	for (p = input->p; isspace(*p); ++p)
		;

	if (*p != '#') {
		if (cppoff)
			*input->p = '\0';
		return cppoff;
	}
	input->p = p+1;

	disexpand = 1;
	lexmode = CPPMODE;
	ns = namespace;
	namespace = NS_CPPCLAUSES;
	next();
	namespace = NS_IDEN;

	if (yytoken == '\n')
		goto ret;

	for (bp = clauses; bp->token && bp->token != yytoken; ++bp)
		;
	if (!bp->token) {
		errorp("incorrect preprocessor directive '%s'", yytext);
		goto ret;
	}

	DBG("CPP %s", yytext);

	/*
	 * create a new context to avoid polish the current context,
	 * and to get all the symbols freed at the end
	 */
	pushctx();
	(*bp->fun)();
	popctx();

	/*
	 * #include changes the content of input->line, so the correctness
	 * of the line must be checked in the own include(), and we have
	 * to skip this tests. For the same reason include() is the only
	 * function which does not prepare the next token
	 */
	if (bp->token == INCLUDE)
		goto ret;

	if (yytoken != '\n' && yytoken != EOFTOK && !cppoff)
		cpperror("trailing characters after preprocessor directive");

ret:
	disescape = 0;
	disexpand = 0;
	lexmode = CCMODE;
	namespace = ns;

	/*
	 * at this point we know that the cpp line is processed, and any error
	 * is generated but as next is called we cannot be sure that input is
	 * valid anymore, but in case of begin valid we want to discard any
	 * pending input in the current line
	 */
	if (input)
		*input->p = '\0';

	return 1;
}

void
ppragmaln(void)
{
	static char file[FILENAME_MAX];
	static unsigned nline;
	char *s;

	putchar('\n');
	if (strcmp(file, filenam)) {
		strcpy(file, filenam);
		s = "#line %u \"%s\"\n";
	} else if (nline+1 != lineno) {
		s = "#line %u\n";
	} else {
		s = "";
	}
	nline = lineno;
	printf(s, nline, file);
}

void
outcpp(void)
{
	int c;
	char *s, *t;

	for (next(); yytoken != EOFTOK; next()) {
		if (onlyheader)
			continue;
		if (yytoken != STRING) {
			printf("%s ", yytext);
			continue;
		}
		for (s = yytext; (c = *s) != '\0'; ++s) {
			switch (c) {
			case '\n':
				t = "\\n";
				goto print_str;
			case '\v':
				t = "\\v";
				goto print_str;
			case '\b':
				t = "\\b";
				goto print_str;
			case '\t':
				t = "\\t";
				goto print_str;
			case '\a':
				t = "\\a";
				goto print_str;
			case '\f':
				t = "\\f";
				goto print_str;
			case '\r':
				t = "\\r";
				goto print_str;
			case '"':
				if (s == yytext || s[1] == '\0')
					goto print_chr;
				t = "\\\"";
				goto print_str;
			case '\'':
				t = "\\'";
				goto print_str;
			case '\?':
				t = "\\\?";
				goto print_str;
			case '\\':
				putchar('\\');
			default:
			print_chr:
				if (!isprint(c))
					printf("\\x%x", c);
				else
					putchar(c);
				break;
			print_str:
				fputs(t, stdout);
				break;
			}
		}
		putchar(' ');
	}
	putchar('\n');
}
