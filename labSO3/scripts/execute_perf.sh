#!/bin/bash

for j in `seq 1 $2`
do
	for i in `seq 1 $1`
	do
		if [ "$i" -eq "$1" ]; then
			perf sched record -a -o "perf.data.$i$j" ./a.out >> "time_process.$i$j.txt"	
		else
			perf sched record -a -o "perf.data.$i$j" ./a.out >> "time_process.$i$j.txt" &
		fi
	done
done
