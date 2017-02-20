#!/bin/bash
echo "Task|Runtime.ms|Switches|Average.delay.ms|Maximum.delay.ms|Maximum.delay.at|Time|N.Of.Processes" >> data_plot.txt
cat result*.txt >> data_plot.txt
