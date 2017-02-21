#!/bin/bash

for j in `seq 1 $2`
do
	for i in `seq 1 $1`
	do
		if [ "$i" -eq "$1" ]; then
			if [ $((($j%2))) == 0 ]; then
				perf sched record -o "perf.data.$i$j" ./a.out $3 >> "time_process.$i$j.txt"
			else
				perf sched record -o "perf.data.$i$j" ./a.out 0 >> "time_process.$i$j.txt"
			fi
		else
			if [ $((($j%2))) == 0 ]; then
				perf sched record -o "perf.data.$i$j" ./a.out $3 >> "time_process.$i$j.txt" &
			else 
				perf sched record -o "perf.data.$i$j" ./a.out 0 >> "time_process.$i$j.txt" &
			fi
		fi
	done
done

