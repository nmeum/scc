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

############################################################################
#print 3rd member

$EXEC scc ar -t file.a file3 > $tmp1
diff -u $tmp1 - <<EOF
file3
EOF

############################################################################
#print 2nd member with verbose

$EXEC scc ar -tv file.a file2 >$tmp1
diff -u $tmp1 - <<EOF
rw-r--r-- `id -u`/`id -g`	Tue Jan  1 00:00:00 1980 file2
EOF

############################################################################
#print all members

$EXEC scc ar -t file.a file1 file2 file3 >$tmp1
diff -u $tmp1 - <<EOF
file1
file2
file3
EOF

#and now with no members in command line

$EXEC scc ar -t file.a > $tmp1
diff -u $tmp1 - <<EOF
file1
file2
file3
EOF
