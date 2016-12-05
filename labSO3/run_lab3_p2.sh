#!/bin/bash

for i in `seq 1 $1`
do 
	perf sched latency ./a.out &
done
