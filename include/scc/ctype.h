#ifndef _CTYPE_H
#define _CTYPE_H

int isalnum(int);
int isalpha(int);
int islower(int);
int isupper(int);
int isdigit(int);
int isxdigit(int);
int iscntrl(int);
int isgraph(int);
int isspace(int);
int isblank(int);
int isprint(int);
int ispunct(int);
int tolower(int);
int toupper(int);


#define _U  0x01 /* upper */
#define _L  0x02 /* lower */
#define _D  0x04 /* digit */
#define _C  0x08 /* cntrl */
#define _P  0x10 /* punct */
#define _S  0x20 /* white space (space/lf/tab) */
#define _X  0x40 /* hex char */
#define _SP 0x80 /* hard space (0x20) */

extern const unsigned char __ctype[];

#define isalnum(c)  ((__ctype+1)[c] & (_U|_L|_D))
#define isalpha(c)  ((__ctype+1)[c] & (_U|_L))
#define iscntrl(c)  ((__ctype+1)[c] & (_C))
#define isdigit(c)  ((__ctype+1)[c] & (_D))
#define isgraph(c)  ((__ctype+1)[c] & (_P|_U|_L|_D))
#define islower(c)  ((__ctype+1)[c] & (_L))
#define isprint(c)  ((__ctype+1)[c] & (_P|_U|_L|_D|_SP))
#define ispunct(c)  ((__ctype+1)[c] & (_P))
#define isspace(c)  ((__ctype+1)[c] & (_S))
#define isupper(c)  ((__ctype+1)[c] & (_U))
#define isxdigit(c) ((__ctype+1)[c] & (_D|_X))

#endif
