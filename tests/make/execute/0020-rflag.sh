#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make -rf test.mk file.o print-makeflags > $tmp1 2>&1

diff $tmp1 - <<EOF
-r
EOF
touch file.c
