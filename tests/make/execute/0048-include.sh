#!/bin/sh

trap 'rm -f $tmp1 $tmp2' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$
tmp2=tmp2.$$

touch $tmp2

$EXEC scc make -f- hello <<EOF > $tmp1 2>&1
FILE = test.mk
F = $tmp2

include \$(FILE)
include \$(F)
EOF

diff $tmp1 - <<EOF
Hello World!
EOF
