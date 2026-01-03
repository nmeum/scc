#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

scc make -nf test.mk print-hidden-hello > $tmp1 2>&1

diff $tmp1 - <<EOF
echo Hello World!
Hello World!
EOF
