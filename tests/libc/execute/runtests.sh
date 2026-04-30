#!/bin/sh

file=${1?' empty input file'}

trap 'rm -f *.o  $tmp1 $tmp2' EXIT
trap 'exit $?' INT QUIT TERM

rm -f test.log

tmp1=tmp1.$$
tmp2=tmp2.$$

while read i state
do
	rm -f *.o $i $tmp1 $tmp2

	(echo $i
	 $CC $CFLAGS $LDFLAGS -o $i $i.c
	 echo '/^output:$/+;/^end:$/-'w $tmp1 | ed -s $i.c

	 $EXEC ./$i >$tmp2 2>&1 &
	 pid=$!
	 sleep 10 && echo timeout >> $tmp2 && kill $pid 2>/dev/null&
	 timer=$!
	 wait $pid
	 kill $timer
	 wait $timer

	 if grep '^RESULT: SKIP$' $tmp2
	 then
		printf '\tSKIP\t%s\n' $i $state
		continue
	 fi
	 diff -u $tmp1 $tmp2) >> test.log 2>&1 &&

	printf '[PASS]' || printf '[FAIL]'
        printf '\t%s\t%s\n' $i $state
done < $file
