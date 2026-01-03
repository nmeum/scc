#!/bin/sh

set -e

trap 'rm -f file* $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

############################################################################
#Update one member that exists and using -a

echo First > file1

cp master.a file.a
$EXEC scc ar -rv -a file1 file.a file1

$EXEC scc ar -p file.a file1 > $tmp1
diff -u $tmp1 - <<EOF
First
EOF

$EXEC scc ar -t file.a > $tmp1
diff -u $tmp1 - <<EOF
file1
file2
file3
EOF
