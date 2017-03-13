#!/bin/bash

t=$(/usr/bin/time -f "%e" ./a.out)

echo $t
