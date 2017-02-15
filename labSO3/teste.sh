#!/bin/bash
time=`(/usr/bin/time -f "%e" ./a.out) 2>&1`
echo "foo: $foo"
PI=$(echo "scale=6; $foo*1000" | bc)
echo "foo: $foo"
echo "PI = $PI"
