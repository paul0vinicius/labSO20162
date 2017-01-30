#!/bin/bash

for j in `seq 1 15`
do
	for i in `seq 1 $1`
	do
		perf sched -i "perf.data.$i$j" latency >> "perf.data.$i$j.txt"
	done
done
