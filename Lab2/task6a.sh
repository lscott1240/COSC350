#!/bin/bash
# diamond.sh - create a diamond from user input size

echo "Input size of the diamond"
read size

oddcheck=`expr $size % 2`

if [ $size -le 3 ]; then
	echo "Input a value greater than 3"
      	exit 1
fi

if [ $oddcheck -eq 0 ]; then
	echo "Input an odd value"
	exit 1
fi

halfsize=`expr $size / 2`
halfsize1=`expr $halfsize - 1`

for i in $(seq 0 $halfsize1);
do
	check1=`expr $halfsize - $i`
	check2=`expr $i \* 2 + 1`

	for j in $(seq $check1 -1 0)
	do
		printf " "
	done

	for j in $(seq $check2 -1 1)
	do
		printf "*"
	done

	printf "\n"
done

printf " "

for i in $(seq 1 $size)
do
	printf "*"
done

for i in $(seq 1 $halfsize)
do
	check3=`expr $size - $i \* 2`

	printf "\n"
	for j in $(seq 0 $i)
	do
		printf " "
	done

	for j in $(seq 1 $check3)
	do
		printf "*"
	done

done
printf "\n"
exit 0;	
