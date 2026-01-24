#!/bin/sh

set -e

trap 'rm -f file.a $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

############################################################################
#print 2nd member with verbose

cp master.a file.a

$EXEC scc ar -pv file.a file2 >$tmp1
diff -u $tmp1 - <<EOF

<file2>

But this other one is the second one,
and it shouldn't go in the first position
because it should go in the second position.
EOF
