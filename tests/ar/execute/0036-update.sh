#!/bin/sh

set -e

trap 'rm -f file* $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

############################################################################
#Update one member that doesn't exist and using -b

echo First > file-1

cp master.a file.a
$EXEC scc ar -rv -b file1 file.a file-1

$EXEC scc ar -p file.a file-1 > $tmp1
diff -u $tmp1 - <<EOF
First
EOF

$EXEC scc ar -t file.a > $tmp1
diff -u $tmp1 - <<EOF
file-1
file1
file2
file3
EOF
