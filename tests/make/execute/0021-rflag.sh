#!/bin/sh

trap 'rm -f $tmp1 file.c file.o' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

touch file.c
MAKEFLAGS=-r \
$EXEC scc make -f test.mk file.o print-makeflags > $tmp1 2>&1

diff $tmp1 - <<EOF
-r
EOF
