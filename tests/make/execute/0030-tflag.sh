#!/bin/sh

trap 'rm -f $tmp1 file.o file.c' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

touch file.c

scc make -tf test.mk file.o > $tmp1 2>&1

diff $tmp1 - <<EOF && test -f file.c -a -f file.o
touch file.c
touch file.o
EOF
