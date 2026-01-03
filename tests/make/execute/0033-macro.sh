#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

scc make -f test.mk CC=pcc print-cc > $tmp1 2>&1

diff $tmp1 - <<EOF
pcc
EOF
