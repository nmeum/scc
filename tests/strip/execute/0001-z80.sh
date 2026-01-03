#!/bin/sh

set -e

trap 'rm -f $tmp1 $tmp2' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$
tmp2=tmp2.$$

cp z80.out $tmp1
scc strip $tmp1 > $tmp2
scc nm $tmp1 >> $tmp2 2>&1 || true

diff $tmp2 - <<EOF
nm: $tmp1: no symbols
EOF
