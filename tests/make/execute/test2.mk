OBJS=\
	$(MOREOBJS)\
	main.o

all:
	@echo MAKEFLAGS='$(MAKEFLAGS)'
	@echo MOREOBJS='$(MOREOBJS)'
	@echo OBJS='$(OBJS)'
	@$(MAKE) -f test2.mk debug

debug:
	@env | grep MAKEFLAGS
	@echo MAKEFLAGS='$(MAKEFLAGS)'
	@echo MOREOBJS='$(MOREOBJS)'
	@echo OBJS='$(OBJS)'
