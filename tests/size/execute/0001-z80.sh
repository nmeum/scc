#!/bin/sh

set -e

trap 'rm -f $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc size z80.out >$tmp1

diff $tmp1 - <<EOF
text	data	bss	dec	hex	filename
5	3	3	11	b	z80.out
EOF
