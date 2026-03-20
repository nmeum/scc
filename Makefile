.POSIX:

SCCMAKE = $$PWD/scripts/scc-make

all: deps

scripts/scc-make:
	$(CC) -o $@ src/cmd/scc-make/*.c

deps: scripts/scc-make
	+@$(SCCMAKE) dep
	touch $@;\

all dep tests install uninstall: scripts/scc-make check_config FORCE
	+@$(SCCMAKE) -f main.mk $@

check_config: scripts/scc-make FORCE
	@if ! test -f config.mk;\
	then\
		$(SCCMAKE) config;\
	fi

config: scripts/scc-make FORCE
	@if ! command -v qbe > /dev/null;\
	then \
		echo "qbe code generator is required to use scc" >&2;\
		exit 1;\
	fi
	mkdir -p bin
	./scripts/config
	@$(SCCMAKE) -f main.mk config

config-musl: scripts/scc-make FORCE
	scripts/muslcfg

clean: FORCE
	touch config.mk
	$(MAKE) -f main.mk clean

dist distclean: FORCE
	touch config.mk
	rm -f scripts/scc-make deps
	$(MAKE) -f main.mk $@

FORCE:
