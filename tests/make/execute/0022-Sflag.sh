#!/bin/sh

trap 'rm -f $tmp1' EXIT 
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

MAKEFLAGS=-k \
$EXEC scc make -Sf test.mk print-makeflags follow 2>&1 |
sed 's/:.*: no-/: no-/' > $tmp1

diff $tmp1 - <<EOF
-k -S
no-valid-program
sh: no-valid-program: not found
make: error: target error: error 32512
EOF
