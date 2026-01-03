#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

MAKEFLAGS=-i \
$EXEC scc make -f test.mk error print-makeflags 2>&1 |
sed 's/sh:.*: *no-/sh: no-/' > $tmp1 2>&1

diff $tmp1 - <<EOF
no-valid-program
sh: no-valid-program: not found
-i
EOF
