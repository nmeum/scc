#!/bin/sh

set -e

trap 'rm -f file.a' EXIT
trap 'exit 1' HUP INT TERM

###########################################################################
#empty file list

rm -f file.a
$EXEC scc ar -qv file.a
if ! test -f file.a
then
	echo "ar -q didn't generated empty archive" >&2
	exit 1
fi
