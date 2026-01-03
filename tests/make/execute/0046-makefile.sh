#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f test.mk -f - hello <<EOF > $tmp1 2>&1
hello:
	@echo Bye world!
EOF

diff $tmp1 - <<EOF
Bye world!
EOF
