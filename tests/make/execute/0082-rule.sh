#!/bin/sh

trap 'rm -f $tmp1 f.c f.o f' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

echo hello > f.c

$EXEC scc make -sf- <<'EOF' > $tmp1 2>&1

.SUFFIXES:

.c:
	echo hello > $@

all: f
EOF

diff $tmp1 - <<EOF
make: error: don't know how to make f
EOF
