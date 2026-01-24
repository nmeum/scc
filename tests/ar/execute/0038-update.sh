#!/bin/sh

set -e

trap 'rm -f file* $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$
tmp2=tmp2.$$

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
