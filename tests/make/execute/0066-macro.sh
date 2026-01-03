#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f- all <<'EOF' > $tmp1 2>&1
VAR2 = one
VAR = $(VAR2)
VAR2 = three

all:
	@echo Hello $(VAR)!

VAR2 = World
EOF

diff $tmp1 - <<EOF
Hello World!
EOF
