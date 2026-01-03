#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1 ' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f - target1 <<EOF > $tmp1 2>&1
#esto es un comentario \
target1: ; echo hello
target2: ; echo bye
EOF

diff $tmp1 - <<EOF
make: error: don't know how to make target1
EOF
