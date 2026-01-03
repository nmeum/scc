#!/bin/sh

set -e

trap 'rm -f file.a $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

############################################################################
#list 1st member

cp master.a file.a

$EXEC scc ar -t file.a file1 > $tmp1
diff -u $tmp1 - <<EOF
file1
EOF
