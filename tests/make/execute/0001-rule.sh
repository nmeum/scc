#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

scc make hello > $tmp1 2>&1

diff $tmp1 - <<EOF
Hello World!
EOF
