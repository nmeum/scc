#!/bin/sh

set -e

trap 'rm -f file.a $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

############################################################################
#print 1st member

cp master.a file.a

$EXEC scc ar -p file.a file1 > $tmp1
diff $tmp1 - <<EOF
This is the first file,
and it should go in the
first position in the archive.
EOF
