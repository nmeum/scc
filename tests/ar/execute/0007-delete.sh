#!/bin/sh

set -e

trap 'rm -f file.a' EXIT
trap 'exit 1' HUP INT TERM

############################################################################
#delete one member

cp master.a file.a

$EXEC scc ar -dv file.a file2

if $EXEC scc ar -tv file.a file2
then
	echo file-2 was not deleted >&2
	exit 1
fi
