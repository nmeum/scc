#!/bin/sh

trap 'rm $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f - <<'EOF' > $tmp1 2>&1
# full line comment
all:
	@echo Hello World!
EOF

diff $tmp1 - <<EOF
Hello World!
EOF
