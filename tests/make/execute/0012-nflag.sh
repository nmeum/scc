#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

(set -e
 $EXEC scc make -f test.mk -n print-makeflags error
 echo correct) > $tmp1 2>&1

diff $tmp1 - <<EOF
echo -n
no-valid-program
correct
EOF
