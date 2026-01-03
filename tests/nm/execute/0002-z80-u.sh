#!/bin/sh

set -e

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

scc nm -u z80.out > $tmp1

diff $tmp1 - <<!
                 U text6
!
