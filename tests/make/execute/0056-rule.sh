#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

echo 'all: ; @echo Hello World!' |
$EXEC scc make -f- > $tmp1 2>&1

diff $tmp1 - <<EOF
Hello World!
EOF
