#!/bin/sh

set -e

trap 'rm -f file* $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

############################################################################
#move 1st at the end

cp master.a file.a
$EXEC scc ar -mv -a file3 file.a file1
$EXEC scc ar -t file.a > $tmp1

diff -u $tmp1 - <<EOF
file2
file3
file1
EOF
