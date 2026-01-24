#!/bin/sh

set -e

trap 'rm -f file* $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

############################################################################
#extract without parameters

cp master.a file.a
$EXEC scc ar -xv file.a

cat file1 file2 file3 > $tmp1
diff -u $tmp1 - <<EOF
This is the first file,
and it should go in the
first position in the archive.
But this other one is the second one,
and it shouldn't go in the first position
because it should go in the second position.
and at the end, this is the last file
that should go at the end of the file,
thus it should go in the third position.
EOF

if test `ls file? | wc -l` -ne 3
then
	echo some error extracting files
	exit 1
fi
