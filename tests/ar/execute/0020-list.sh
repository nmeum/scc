#!/bin/sh

set -e

trap 'rm -f file.a $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

############################################################################
#print 2nd member with verbose

cp master.a file.a

$EXEC scc ar -tv file.a file2 >$tmp1
diff $tmp1 - <<EOF
rw-r--r-- `id -u`/`id -g`	Tue Jan  1 00:00:00 1980 file2
EOF
