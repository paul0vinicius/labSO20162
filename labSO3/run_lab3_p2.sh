#!/bin/bash

for j in `seq 1 15`
do
	for i in `seq 1 $1`
	do
		if [ "$i" -eq "$1" ]; then
			#time=`(/usr/bin/time -f "%e" ./a.out) 2>&1`
			time=`(/usr/bin/time -f "%e" perf sched record -o "perf.data.$i$j" ./a.out) 2>&1`
			echo "scale=3; $time*1000" | bc >> time_process.$i$j.txt
		else 
			time=`(/usr/bin/time -f "%e" perf sched record -o "perf.data.$i$j" ./a.out) 2>&1`
			echo "scale=3; $time*1000" | bc >> time_process.$i$j.txt &
		fi
	done
	
done

