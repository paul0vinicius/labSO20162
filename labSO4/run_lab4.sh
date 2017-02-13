#!/bin/bash

for j in `seq 1 15`
do
	for i in `seq 1 $1`
	do
		if [ "$i" -eq "$1" ]; then
			if [$j % 2 = 0]; then 
				perf sched record -o "perf.data.$i$j" ./a.out $2
			else
				perf sched record -o "perf.data.$i$j" ./a.out $2
			fi
		else 
			if [$j % 2 = 0]; then 
				perf sched record -o "perf.data.$i$j" ./a.out $2 &
			else
				perf sched record -o "perf.data.$i$j" ./a.out $2 &
			fi
		fi
	done
	
done

