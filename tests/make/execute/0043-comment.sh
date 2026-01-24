#!/bin/sh

trap 'rm $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f - <<'EOF' > $tmp1 2>&1
all:
	@echo Hello World!
# blank line
EOF

diff $tmp1 - <<EOF
Hello World!
EOF
