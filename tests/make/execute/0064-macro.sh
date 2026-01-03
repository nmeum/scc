#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

scc make -f- all <<'EOF' > $tmp1 2>&1
VAR = guy

all:
	@echo Hello $(VAR)!
VAR = World
EOF

diff $tmp1 - <<EOF
Hello World!
EOF
