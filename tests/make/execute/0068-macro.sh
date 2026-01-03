#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f- <<'EOF' > $tmp1 2>&1
SRC = file1.c file2.c

all:
	@echo $(SRC:.c=.o)
EOF

diff $tmp1 - <<EOF
file1.o file2.o
EOF
