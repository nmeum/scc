#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f- all <<'EOF' > $tmp1 2>&1
VAR = VAR2

$(VAR) = World

all:
	@echo Hello $(VAR2)!
EOF

diff $tmp1 - <<EOF
Hello World!
EOF
