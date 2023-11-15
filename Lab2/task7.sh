#!/bin/bash
# task7.sh - Factorial calculator, while loop

echo "Input number for factorial"
read factorial

total=1

while [ $factorial -gt 1 ];
do
	total=`expr $factorial \* $total`
	let factorial--
done

echo $total

