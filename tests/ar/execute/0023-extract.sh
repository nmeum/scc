#!/bin/sh

set -e

trap 'rm -f file*' EXIT
trap 'exit 1' HUP INT TERM

############################################################################
#extract 1st member

cp master.a file.a

$EXEC scc ar -xv file.a file1
diff -u file1 - <<EOF
This is the first file,
and it should go in the
first position in the archive.
EOF
