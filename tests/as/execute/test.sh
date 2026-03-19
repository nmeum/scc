#!/bin/sh

set -e
cpu=${1?'missed cpu argument'}
exec >>test.log
exec 2>&1

tmp1=tmp1.$$
tmp2=tmp2.$$
file=$cpu.s

trap 'rm -f a.out $tmp1 $tmp2' EXIT
trap 'exit $?' HUP INT TERM

$EXEC scc as -m $cpu $file

sed -n '/^\#/ ! {
	/\#/ ! d
	s%.*#%%
	s%^[ 	]*%%
	s%[ 	]*$%%
	/^$/d
	s%[ 	][ 	]*%\
%g
	p
}' $file |
nl -b a > $tmp1

od -An -t x1 a.out |
tr 'a-z' 'A-Z' |
sed -n 's%.*:%%
	s%^[ 	]*%%
	s%[ 	]*$%%
	/^$/d
	s%[ 	][ 	]*%\
%g
	p' |
nl -b a > $tmp2

diff -u $tmp1 $tmp2
