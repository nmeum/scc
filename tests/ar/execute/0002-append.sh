#!/bin/sh

set -e

trap 'rm -f file* $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

###########################################################################
#Append generated files one by one to an empty file

echo First > file1
echo Second > file2
echo Third > file3

rm -f file.a
$EXEC scc ar -qv file.a file1
$EXEC scc ar -qv file.a file2
$EXEC scc ar -qv file.a file3

$EXEC scc ar -t file.a > $tmp1
diff -u $tmp1 - <<EOF
file1
file2
file3
EOF

$EXEC scc ar -p file.a > $tmp1
diff -u $tmp1 - <<EOF
First
Second
Third
EOF
