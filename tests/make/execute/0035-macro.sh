#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

MAKEFLAGS='-S CC=pcc' \
$EXEC scc make -f test.mk print-env-cc > $tmp1 2>&1

diff $tmp1 - <<EOF

EOF
