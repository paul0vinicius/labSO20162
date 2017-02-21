#!/bin/bash

cat perf*.txt | grep a.out >> filtrado.txt
cat time*.txt >> all_time.txt
