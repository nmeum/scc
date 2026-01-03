#!/bin/sh

set -e

trap 'rm -f file* $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=`mktemp`
tmp2=`mktemp`

############################################################################
#Update without parameters

cp master.a file.a
$EXEC scc ar -rv file.a

$EXEC scc ar -t file.a > $tmp1
diff -u $tmp1 - <<EOF
file1
file2
file3
EOF
