#!/bin/sh

set -e

trap 'rm -f file* $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

###########################################################################
#Append generated files at once to an existing archive

echo First > file-1
echo Second > file-2
echo Third > file-3

cp master.a file.a
$EXEC scc ar -qv file.a file-1 file-2 file-3

$EXEC scc ar -t file.a file-1 file-2 file-3 > $tmp1
diff -u $tmp1 - <<EOF
file-1
file-2
file-3
EOF

$EXEC scc ar -p file.a file-1 file-2 file-3 > $tmp1
diff -u $tmp1 - <<EOF
First
Second
Third
EOF
