#!/bin/sh

trap 'rm -f $tmp1 $tmp2 file?' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$
tmp2=tmp2.$$

touch $tmp2

touch file2
touch file3

$EXEC scc make -f test.mk file3  > $tmp1 2>&1

diff $tmp1 - <<EOF
EOF
