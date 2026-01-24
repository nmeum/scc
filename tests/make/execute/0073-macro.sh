#!/bin/sh

trap 'rm -f $tmp1 $tmp2' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

CC=dcc \
$EXEC scc make -f- <<'EOF' > $tmp1 2>&1
CC=tcc

all:
	@echo CC=$(CC)
EOF

diff $tmp1 - <<EOF
CC=tcc
EOF
