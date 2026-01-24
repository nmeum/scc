#!/bin/sh

set -e

trap 'rm -f file.a' EXIT
trap 'exit $?' HUP INT TERM

###########################################################################
#recursive inclusion

rm -f file.a
$EXEC scc ar -qv file.a file.a
