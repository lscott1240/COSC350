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


for i in $(seq 0 $halfsize)
do
	check1=`expr $i \* 2`

	for j in $(seq 1 $tailsize)
	do
		printf " "
	done

	for j in $(seq 0 $check1)
	do
		printf "*"
	done

	printf "\n"
done

total=`expr $tailsize + $size`

for i in $(seq 1 $total)
do
	printf "*"
done

printf "\n"

for i in $(seq 0 $halfsize)
do
	check2=`expr $size1 - 2 \* $i - 2`

	for j in $(seq 1 $tailsize)
	do
		printf " "
	done

	for j in $(seq 1 $check2)
	do
		printf "*"
	done
	
	printf "\n"
done

printf "\n"
exit 0;
