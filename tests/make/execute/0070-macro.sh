#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f- <<'EOF' > $tmp1 2>&1
VAR1 = one
VAR = $(VAR1)
VAR1 = print

all: $(VAR)

print:
	@echo Hello World!
VAR1 = two

EOF

diff $tmp1 - <<EOF
Hello World!
EOF
