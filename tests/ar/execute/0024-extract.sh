#!/bin/sh

set -e

trap 'rm -f file*' EXIT
trap 'exit $?' HUP INT TERM

############################################################################
#extract 3rd member

cp master.a file.a

$EXEC scc ar -xv file.a file3
diff -u file3 - <<EOF
and at the end, this is the last file
that should go at the end of the file,
thus it should go in the third position.
EOF
