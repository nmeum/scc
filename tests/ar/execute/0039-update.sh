#!/bin/sh

set -e

trap 'rm -f file* $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

############################################################################
#Update one member that already exist

echo First > file1

cp master.a file.a
sleep 1
touch file1
$EXEC scc ar -ruv file.a file1

$EXEC scc ar -p file.a file1 > $tmp1
diff -u $tmp1 - <<EOF
First
EOF

echo Second > file1
touch -t 197001010000 file1
$EXEC scc ar -ruv file.a file1

$EXEC scc ar -p file.a file1 > $tmp1
diff -u $tmp1 - <<EOF
First
EOF
