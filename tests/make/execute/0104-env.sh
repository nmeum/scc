#!/bin/sh

export CFLAGS=World

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f - <<'EOF' > $tmp1 2>&1
FLAGS=Hello $(CFLAGS)
all:
	@echo Hello $(CFLAGS)
EOF

diff $tmp1 - <<EOF
Hello World
EOF
