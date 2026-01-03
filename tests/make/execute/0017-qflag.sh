#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

(set -e
 scc make -qf test.mk error
 echo fail) > $tmp1 2>&1

diff $tmp1 - <<EOF
EOF
