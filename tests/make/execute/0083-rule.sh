#!/bin/sh

trap 'rm -f $tmp1 f.c f.o' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

echo dude > f.c

($EXEC scc make -f- <<'EOF'
f.o:
	@echo hello > $@

all: f.o
EOF
cat f.o) > $tmp1 2>&1

diff $tmp1 - <<EOF
hello
EOF
