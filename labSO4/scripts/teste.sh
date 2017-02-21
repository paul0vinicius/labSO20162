#!/bin/bash

for j in `seq 1 $2`
do
	for i in `seq 1 $1`
	do
	echo $((($j%2)))
	echo $j
		if [ "$i" -eq "$1" ]; then
			if [ $((($j%2))) == 0 ]; then
				
				echo 'entrou na cond'
			else
				echo 'entrou na cond2'
			fi
		else
			if [ $((($j%2))) == 0 ]; then
				echo 'entrou na cond3'
			else
				echo 'entrou na cond4'
			fi
		fi
	done
done
