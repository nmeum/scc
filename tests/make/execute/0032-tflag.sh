#!/bin/sh

trap 'rm -f $tmp1 $tmp2 file1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$
tmp2=tmp2.$$

touch $tmp2

$EXEC scc make -stf test.mk file1 > $tmp1 2>&1

diff $tmp1 $tmp2 && test -f file1
