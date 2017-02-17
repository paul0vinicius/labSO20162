#!/bin/bash

sed 's/ //g' $1 | sed 's/ms//g'| sed 's/s//g' | sed 's/avg//g' | sed 's/max//g' | sed 's/at//g' | sed 's/://g' > final_data.txt
