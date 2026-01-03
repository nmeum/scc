#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f- <<EOF > $tmp1 2>&1
hello:
	@echo Hello World!;\
echo Bye World!
EOF

diff $tmp1 - <<EOF
Hello World!
Bye World!
EOF
