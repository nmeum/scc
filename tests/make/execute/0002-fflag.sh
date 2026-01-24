#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f test.mk print-cc print-makeflags > $tmp1 2>&1

diff $tmp1 - <<EOF
c99

EOF
