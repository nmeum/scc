#!/bin/sh

trap 'rm -f $tmp f.c f.o f' EXIT
trap 'exit $?' HUP INT TERM

tmp=tmp.$$

echo hello > $tmp

echo hello > f.c

$EXEC scc make -sf- <<'EOF'
.c.o:
	cp $< $@

all: f.o
EOF

diff $tmp f.o
