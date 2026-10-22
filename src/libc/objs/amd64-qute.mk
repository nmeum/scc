include objs/common-objs.mk

OBJS =\
	$(COMMON_OBJS)\
	arch/qute/_brk.$O\
	arch/qute/_exit.$O\
	arch/qute/_read.$O\
	arch/qute/_write.$O\
	arch/qute/_getheap.$O\
	string/memchr.$O\
	string/memcmp.$O\
	string/memcpy.$O\
	string/memmove.$O\
	string/memmove.$O\
	string/memset.$O\
	string/strlen.$O\
