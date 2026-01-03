#!/bin/sh

trap 'rm -f $tmp1 print-makeflags-always' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

MAKEFLAGS=-t scc make -f test.mk print-makeflags-always > $tmp1 2>&1

diff -u $tmp1 - <<EOF && test -f print-makeflags-always
-t
touch print-makeflags-always
EOF
