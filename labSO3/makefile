run_all: clean compile
	./run_lab3_p2.sh 1 15
	./run_lab3_p2.sh 4 15
	./run_lab3_p2.sh 8 15
	./scripts/concatena_tudo.sh
	./plot_lab3_p2.sh

compile:
	gcc cpu_burn.c

clean:
	rm -rf execucao_* a.out data_plot.txt result*.txt *.pdf
