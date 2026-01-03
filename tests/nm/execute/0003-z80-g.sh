#!/bin/sh

set -e

trap 'rm -f $tmp1' EXIT
trap 'exit 1' HUP INT TERM

tmp1=tmp1.$$

scc nm -g z80.out > $tmp1

diff $tmp1 - <<!
0000000000000001 B averylongbss
0000000000000001 D averylongdata
0000000000000001 T averylongtext
0000000000000000 B bss1
000000000000000a C bss4
0000000000000012 C bss5
0000000000000000 D data1
000000000000000a C data4
0000000000000012 C data5
0000000000000000 T text1
000000000000000a C text4
0000000000000012 C text5
                 U text6
!
