#!/bin/sh

set -e

trap 'rm -f $tmp1' EXIT
trap 'exit $?' HUP INT TERM

tmp1=tmp1.$$

$EXEC scc nm -u z80.out > $tmp1

diff $tmp1 - <<!
                 U text6
!
