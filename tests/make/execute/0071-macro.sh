#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

CC=dcc MAKEFLAGS='-S CC=gcc' \
$EXEC scc make -f- CC=pcc <<'EOF' > $tmp1 2>&1
CC=tcc

all:
	@echo CC=$(CC)
EOF

diff $tmp1 - <<EOF
CC=pcc
EOF
