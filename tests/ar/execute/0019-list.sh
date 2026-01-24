#!/bin/sh

set -e

trap 'rm -f file.a $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=`mktemp`

############################################################################
#print 3rd member

cp master.a file.a

$EXEC scc ar -t file.a file3 > $tmp1
diff -u $tmp1 - <<EOF
file3
EOF
