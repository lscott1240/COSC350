#!/bin/bash
#task9.sh File manipulation
cd
echo -n "Enter file path: "
read filepath

if [ -d "$filepath" ];then
	echo "This path exists"
else
	echo "No such directory"
	exit 1;
fi

cd -e $filepath

echo -n "Enter file name: "
read filename

for i in $(seq 0 3)
do
	if [ -e "$filename" ];then
		if [ -e "$filename" ];then
			echo "File exits and is readable"
			break
		else
			echo "File is not readable"
			exit 3
		fi
	else
		echo -n "File does not exist, enter a file that exists: "
		read filename
		continue
	fi

	if [ $i -eq 2 ];then
		echo "No such file (after three attempts)"
		exit 2
	fi
done

echo -n "Enter the word you would like to search for: "
read search

wordfound=$(grep -c $search $filename)
if [ $wordfound -gt 0 ];then
	echo "Word found"
else
	echo "Word not found in the file"
	exit 4
fi

echo "Success"
exit 0
