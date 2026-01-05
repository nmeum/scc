#ifndef BITS_WCHAR_H
#define BITS_WCHAR_H
typedef struct {
	unsigned char oc;
	unsigned char sh;
	__wchar_t wc;
} __mbstate_t;
#endif
