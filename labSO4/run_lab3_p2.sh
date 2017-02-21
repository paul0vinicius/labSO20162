#!/bin/bash

./scripts/execute_perf.sh $1 $2 $3
./scripts/data_generator.sh $1 $2 $3

mkdir execucao_$1_processos
mv perf* execucao_$1_processos
mv time* execucao_$1_processos

cd execucao_$1_processos
shopt -s extglob
rm -f !(*.txt)
../scripts/filtra_cpuburn.sh
../scripts/refina_arquivos.sh filtrado.txt
../scripts/insere_linha.sh $1 $2 final_data.txt all_time.txt result$1
mv result$1.txt ../
cd ..
