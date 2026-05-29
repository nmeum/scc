#ifndef _STDIO_H
#define _STDIO_H

#define _NEED_NULL
#define _NEED_SIZET
#include <sys/stdio.h>
#include <arch/cdefs.h>
#include <bits/wchar.h>

#ifndef FOPEN_MAX
#define FOPEN_MAX 12
#endif

#define EOF     -1
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

/**
 * enum _file_flags - internal FILE macros used by stdio
 * @_IOWRITE: write only stream
 * @_IOREAD: read only stream
 * @_IORW: read and write stream
 * @_IOEOF: mark of end of file in the stream
 * @_IOERR: mark of error in the stream
 * @_IOSTRG: string stream
 * @_IOTXT: text stream
 * @_IOFBF: full buffered stream
 * @_IOLBF: line buffered stream
 * @_IONBF: non buffered stream
 * @_IOALLOC: stream with a dynamic allocated buffer
 */
enum _file_flags {
	_IOWRITE = (1 << 0),
	_IOREAD =  (1 << 1),
	_IORW =    (1 << 2),
	_IOEOF =   (1 << 3),
	_IOERR =   (1 << 4),
	_IOSTRG =  (1 << 5),
	_IOTXT =   (1 << 6),
	_IOFBF =   (1 << 7),
	_IOLBF =   (1 << 8),
	_IONBF =   (1 << 9),
	_IOALLOC = (1 <<10),
};

/**
 * struct FILE - opaque structure containing information about a file
 * @fd: file descriptor
 * @buf: pointer to i/o buffer
 * @rp: read pointer
 * @wp: write pointer
 * @lp: write pointer used when line-buffering
 * @len: actual length of buffer
 * @flags: file open mode
 * @unbuf: tiny buffer for unbuffered i/o
 */
typedef struct _FILE {
	int fd;
	unsigned char *buf;
	unsigned char *rp;
	unsigned char *wp;
	unsigned char *lp;
	size_t len;
	unsigned short flags;
	unsigned char unbuf[1];
	__mbstate_t mbs;
} FILE;

extern FILE __iob[FOPEN_MAX];

#define	stdin  (&__iob[0])
#define	stdout (&__iob[1])
#define	stderr (&__iob[2])

int remove(const char *);
int rename(const char *, const char *);
FILE *tmpfile(void);
char *tmpnam(char *);

FILE *fopen(const char *restrict, const char *restrict);
FILE *freopen(const char *restrict, const char *restrict,
                     FILE *restrict);
int fclose(FILE *);
int fflush(FILE *);
void setbuf(FILE *restrict, char *restrict);
int setvbuf(FILE *restrict, char *restrict, int, size_t);

int fprintf(FILE *restrict, const char *restrict, ...);
int printf(const char *restrict, ...);
int snprintf(char *restrict, size_t, const char *restrict, ...);
int sprintf(char *restrict, const char *restrict, ...);
int vfprintf(FILE *restrict, const char *restrict, __va_list);
int vprintf(const char *restrict, __va_list);
int vsnprintf(char *restrict, size_t, const char *restrict, __va_list);
int vsprintf(char *restrict, const char *restrict, __va_list);

int fscanf(FILE *restrict, const char *restrict, ...);
int scanf(const char *restrict, ...);
int sscanf(const char *restrict, const char *restrict, ...);
int vfscanf(FILE *restrict, const char *restrict, __va_list);
int vscanf(const char *restrict, __va_list);
int vsscanf(const char *restrict, const char *restrict, __va_list);

int fgetc(FILE *);
char *fgets(char *restrict, int, FILE *restrict);
int getc(FILE *);
int getchar(void);
char *gets(char *);

int fputc(int, FILE *);
int fputs(const char *restrict, FILE *restrict);
int putc(int, FILE *);
int putchar(int);
int puts(const char *);
int ungetc(int, FILE *);

size_t fread(void *restrict, size_t, size_t, FILE *restrict);
size_t fwrite(const void *restrict, size_t, size_t, FILE *restrict);

int fseek(FILE *, long int, int);
long int ftell(FILE *);
void rewind(FILE *);
void clearerr(FILE *);
int feof(FILE *);
int ferror(FILE *);
void perror(const char *);

int __getc(FILE *);
int __putc(int, FILE *);

#define getc(fp)            ((fp)->rp >= (fp)->wp ? __getc(fp) : *(fp)->rp++)
#define putc(c, fp)         ((fp)->wp >= (fp)->rp ? __putc(c,fp) : (*(fp)->wp++ = c))
#define ferror(fp)          ((fp)->flags & _IOERR)
#define feof(fp)            ((fp)->flags & _IOEOF)
#define clearerr(fp)        (void) ((fp)->flags &= ~(_IOERR|_IOEOF))
#define getchar()           getc(stdin)
#define putchar(c)          putc((c), stdout)
#define setbuf(fp, b)       (void) setvbuf(fp, b, b ? _IOFBF:_IONBF, BUFSIZ)

#endif
