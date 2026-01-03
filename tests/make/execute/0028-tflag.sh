#!/bin/sh

trap 'rm -f $tmp1 file1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

scc make -tf test.mk file1 > $tmp1 2>&1

diff $tmp1 - <<EOF && test -f file1
touch file1
EOF
