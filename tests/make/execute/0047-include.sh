#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f- hello <<EOF > $tmp1 2>&1
include test.mk
EOF

diff $tmp1 - <<EOF
Hello World!
EOF
