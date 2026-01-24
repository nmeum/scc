#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f- <<'EOF' > $tmp1 2>&1
VAR = hello
all:
	@echo ${VAR}-$(VAR)
EOF

diff $tmp1 - <<EOF
hello-hello
EOF
