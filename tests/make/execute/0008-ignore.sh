#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -f test.mk ignored-error hello  2>&1 |
sed 's/sh:.*: *no-/sh: no-/' > $tmp1 2>&1

diff $tmp1 - <<EOF
no-valid-program
sh: no-valid-program: not found
Hello World!
EOF
