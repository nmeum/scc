#!/bin/sh

set -e

trap 'rm -f file.a' EXIT
trap 'exit $?' HUP INT TERM

###########################################################################
#empty file list

rm -f file.a
if $EXEC scc ar -qv file.a badfile.a
then
	echo "ar -q failed to detect missed file" >&2
	exit 1
fi
