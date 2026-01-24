#!/bin/sh

trap 'rm -f $tmp1 file2' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -tf test.mk file2 > $tmp1 2>&1

diff $tmp1 - <<EOF && ! test -f file2
EOF
