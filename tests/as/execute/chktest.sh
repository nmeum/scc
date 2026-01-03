#!/bin/sh

rm -f test.log

for i in *.s
do
	cpu="${i%.s}"
	printf "Test: %s\n\n" $cpu >> test.log
	(./test.sh  $cpu >> test.log 2>&1 && printf '[PASS]\t' || printf '[FAIL]\t'
	echo testing cpu=$cpu) | tee -a test.log
done
