#!/bin/bash

for j in `seq 1 15`
do
	for i in `seq 1 $1`
	do
		if [ "$i" -eq "$1" ]; then
			perf sched record -o "perf.data.$i$j" ./a.out
		else 
			perf sched record -o "perf.data.$i$j" ./a.out &
		fi
	done
	
done

