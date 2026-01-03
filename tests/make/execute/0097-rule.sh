#!/bin/sh

trap 'rm -f f1.? $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f- <<'EOF' > $tmp1 2>&1
all: f1.o

f1.o: f1.c
	touch $@

f1.c:
	touch $@
EOF

diff $tmp1 - <<EOF
touch f1.c
touch f1.o
EOF
