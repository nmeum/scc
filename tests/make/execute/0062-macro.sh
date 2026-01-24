#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f- all <<'EOF' > $tmp1 2>&1
TARGET = all

$(TARGET):
	@echo Hello World!
EOF

diff $tmp1 - <<EOF
Hello World!
EOF
