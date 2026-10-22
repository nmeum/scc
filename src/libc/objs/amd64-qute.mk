include objs/common-objs.mk

OBJS =\
	$(COMMON_OBJS)\
	arch/qute/_brk.$O\
	arch/qute/_exit.$O\
	arch/qute/_read.$O\
	arch/qute/_write.$O\
	arch/qute/_getheap.$O\
	string/strlen.$O\
