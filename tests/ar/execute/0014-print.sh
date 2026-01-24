#!/bin/sh

set -e

trap 'rm -f file.a $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

############################################################################
#print 3rd member

cp master.a file.a

$EXEC scc ar -p file.a file3 > $tmp1
diff -u $tmp1 - <<EOF
and at the end, this is the last file
that should go at the end of the file,
thus it should go in the third position.
EOF
