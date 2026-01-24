#!/bin/sh

set -e

trap 'rm -f file* $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

############################################################################
#Update one member that already exist

echo First > file1

cp master.a file.a
$EXEC scc ar -rv file.a file1

$EXEC scc ar -p file.a file1 > $tmp1
diff -u $tmp1 - <<EOF
First
EOF
