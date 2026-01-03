#!/bin/sh

file=${1?' empty input file'}

trap 'rm -f *.o  $tmp1 $tmp2' EXIT
trap 'exit 1' INT QUIT TERM

rm -f test.log

tmp1=tmp1.$$
tmp2=tmp2.$$

while read i state
do
	rm -f *.o $i $tmp1 $tmp2

	(echo $i
	 $CC $CFLAGS -o $i $i.c
	 echo '/^output:$/+;/^end:$/-'w $tmp1 | ed -s $i.c
	 ./$i > $tmp2 2>&1
	 diff -u $tmp1 $tmp2) >> test.log 2>&1 &&

	printf '[PASS]' || printf '[FAIL]'
        printf '\t%s\t%s\n' $i $state
done < $file
