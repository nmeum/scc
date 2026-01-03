#!/bin/sh

trap 'rm -f $tmp1 t1.c t?.o t2' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

echo Hello > t1.c

scc make -f- <<'EOF' > $tmp1 2>&1
.c.o:
	@echo $* > $@

all: t1.o t2.o t2
	@cat t1.o t2.o t2

t2.o:
	@echo $* > $@

t2:
	@echo $* > $@
EOF

diff $tmp1 - <<EOF
t1
t2
t2
EOF
