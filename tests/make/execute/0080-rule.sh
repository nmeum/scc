#!/bin/sh

trap 'rm -f $tmp f.c f.o f' EXIT
trap 'exit 1' HUP INT TERM

tmp=tmp.$$

echo hello > $tmp

echo hello > f.c

scc make -sf- <<'EOF'
.c.o:
	cp $< $@

all: f.o
EOF

diff $tmp f.o
