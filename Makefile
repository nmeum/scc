.POSIX:

SMAKE = $$PWD/scc-make

all: deps

scc-make:
	$(CC) -o $@ src/cmd/scc-make/*.c

deps: scc-make
	+@$(SMAKE) dep
	touch $@;\

all dep tests install uninstall: scc-make check_config FORCE
	+@$(SMAKE) -f main.mk $@

check_config: scc-make FORCE
	@if ! test -f config.mk;\
	then\
		$(SMAKE) config;\
	fi

config: scc-make FORCE
	@if ! command -v qbe > /dev/null;\
	then \
		echo "qbe code generator is required to use scc" >&2;\
		exit 1;\
	fi
	mkdir -p bin
	$(CC) -o scc-make src/cmd/scc-make/*.c
	./scripts/config
	@$(SMAKE) -f main.mk config

config-musl: scc-make FORCE
	$(SMAKE) LIBPROFILE=musl config
	gcc -v 2>&1 |\
	sed -En '/COLLECT_LTO_WRAPPER=/ s/.*=(.*)\/lto-wrapper/\1/p' |\
	(read -r path; \
	 printf "g/define GCCLIBPATH/ s@.*@#define GCCLIBPATH \"$$path/\"@\nw\n") |\
	ed -s include/bits/scc/sys.h

clean: FORCE
	touch config.mk
	$(MAKE) -f main.mk clean

distclean: clean FORCE
	touch config.mk
	$(MAKE) -f main.mk distclean
	rm -f config.mk deps scc-make

FORCE:
