#!/bin/bash

for i in `seq 1 $((15*$1))`
do
	a=$(sed "${i}q;d" $2)
	b=$(sed "${i}q;d" $3)
	echo "$a|$b|$1" >> $4.txt
done

