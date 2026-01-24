#!/bin/sh

set -e

trap 'rm -f file.a $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

############################################################################
#print all members

cp master.a file.a

$EXEC scc ar -t file.a file1 file2 file3 >$tmp1
diff -u $tmp1 - <<EOF
file1
file2
file3
EOF
