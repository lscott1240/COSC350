#!/bin/bash
#task8.sh - Print sum of number

total=0

test1=$*

i=0
for var in "$@"
do
	i=`expr $i + 1`
	if [ $i -gt 1 ];
	then
		echo "Too many arguments"
		exit 1
	fi
done

while [ $test1 -gt 0 ]
do
	remainder=`expr $test1 % 10`
	test1=`expr $test1 / 10`
	total=`expr $total + $remainder`
done

echo $total

exit 0
