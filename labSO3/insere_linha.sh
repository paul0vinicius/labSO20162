#!/bin/bash

cat $1 | while read line
do
	cat $2 | while read line2
	do
		echo "$line|$line2|$3" >> new.txt
	done
	continue
done
