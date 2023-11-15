#!/bin/bash
#leftarrow.sh

echo "Input size of the arrow"
read size

size1=$size
oddcheck=`expr $size1 % 2`

if [ $size1 -le 3 ]; then
	echo "Input a value greater than 3"
	exit 1
fi

if [ $oddcheck -eq 0 ]; then
	echo "Input an odd value"
	exit 1
fi

echo "Input size of the tail"
read tailsize

halfsize=`expr $size1 / 2 - 1`

printf "\n"

for i in $(seq 0 $halfsize)
do
	check1=`expr $size1 - 2 - $i \* 2`
	check2=`expr $i \* 2`

	for j in $(seq $check1 -1 0)
	do
		printf " "
	done

	for j in $(seq 0 $check2)
	do
		printf "*"
	done

	printf "\n"
done

total=`expr $size1 + $tailsize`

for i in $(seq 1 $total)
do
	printf "*"
done

halfsize2=`expr $size / 2`

for k in $(seq 1 $halfsize2)
do
	check3=`expr $k \* 2 - 1`
	check4=`expr $size - 2 \* $k`
	printf "\n"
	for j in $(seq 0 $check3)
	do
		printf " "
	done

	for j in $(seq 1 $check4)
	do
		printf "*"
	done
done

printf "\n"
exit 0;
