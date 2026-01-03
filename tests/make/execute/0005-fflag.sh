#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

MAKEFLAGS=ffff.mk scc make -f test.mk print-cc print-makeflags > $tmp1 2>&1

diff $tmp1 - <<EOF
c99

EOF
