#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f- <<'EOF' > $tmp1 2>&1
VAR1 = one
VAR = Hello $(VAR1)
VAR1 = two

all:
	@echo $(VAR)!
VAR1 = World

EOF

diff $tmp1 - <<EOF
Hello World!
EOF
