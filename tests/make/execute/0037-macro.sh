#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

make=`command -v scc-make`
$make -f test.mk print-make > $tmp1 2>&1

diff $tmp1 - <<EOF
$make
EOF
