#!/bin/sh

set -e

trap 'rm -f file* $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

############################################################################
#Update one member that doesn't exist

echo First > file-1

cp master.a file.a
$EXEC scc ar -rv file.a file-1

$EXEC scc ar -p file.a file-1 > $tmp1
diff -u $tmp1 - <<EOF
First
EOF
