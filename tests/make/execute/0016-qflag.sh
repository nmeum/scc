#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

(set -e
 $EXEC scc make -qf test.mk test.mk
 echo pass) > $tmp1 2>&1

diff $tmp1 - <<EOF
pass
EOF
