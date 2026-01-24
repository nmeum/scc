#!/bin/sh

trap 'rm -f $tmp1 makefile' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

cat > makefile <<EOF
hello:
	@echo Hello World!, makefile!
EOF

$EXEC scc make > $tmp1 2>&1

diff $tmp1 - <<EOF
Hello World!, makefile!
EOF
