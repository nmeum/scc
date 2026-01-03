#!/bin/sh

set -e

cleanup()
{
	st=$?
	rm -f file* $tmp1 $tmp2
	exit $st
}

trap 'rm -f file* $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

############################################################################
#and now, test without parameters

cp master.a file.a
$EXEC scc ar -mv file.a
$EXEC scc ar -t file.a > $tmp1

diff -u $tmp1 - <<EOF
file1
file2
file3
EOF
