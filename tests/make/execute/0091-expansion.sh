#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f- <<'EOF' > $tmp1 2>&1
STARGET = all

b.$(STARGET): b$(STARGET)
	@echo Hello World!

ball:
	@echo But before!
EOF

diff -u $tmp1 - <<EOF
But before!
Hello World!
EOF
