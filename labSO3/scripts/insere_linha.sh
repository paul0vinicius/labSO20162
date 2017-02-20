#!/bin/bash

for i in `seq 1 $(($1*$2))`
do
	a=$(sed "${i}q;d" $3)
	b=$(sed "${i}q;d" $4)
	echo "$a|$b|$1p" >> $5.txt
done

