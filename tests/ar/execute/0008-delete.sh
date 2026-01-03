#!/bin/sh

set -e

trap 'rm -f file.a' EXIT
trap 'exit 1' HUP INT TERM

############################################################################
#delete two members, 1st and 2nd

cp master.a file.a

$EXEC scc ar -dv file.a file1 file2

if $EXEC scc ar -tv file.a file1 file2
then
	echo file1 or file2 were not deleted >&2
	exit 1
fi
