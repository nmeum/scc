#!/bin/sh

trap 'rm -f $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc make no-file > $tmp1 2>&1

diff $tmp1 - <<EOF
make: error: don't know how to make no-file
EOF
