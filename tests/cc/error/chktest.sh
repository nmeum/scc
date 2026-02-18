#!/bin/sh

file=${1?' empty input file'}
err=/tmp/$$.err
chk=/tmp/$$.chk

trap 'rm -f a.out *.o $chk $err; exit' EXIT HUP INT TERM
ulimit -c 0
rm -f test.log

while read i state
do
	echo $i >> test.log
	state=${state:-""}

	(SCCPREFIX=$SCCPREFIX $CC $CFLAGS -w -c $i) 2> $err
	(echo "/^PATTERN/+;/^\./-w $chk" | ed -s $i) >/dev/null 2>&1
	(diff -u $chk $err >> test.log  && printf '[PASS]' || printf '[FAIL]'
	 printf "\t%s\t%s\n" $i $state) | tee -a test.log
	rm -f *.o
done < $file
