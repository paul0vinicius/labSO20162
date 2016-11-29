#include <unistd.h>
#include <stdio.h>

/* Definição de uma função para imprimir msg de erros graves, abortando o
 * código */
char erro(char *m)
{
	fprintf(stderr, "ERRO: %s\n", m);
	exit(1);
}


main()
{
	int fda[2];
	/* Será usado para guardar o número descritor dos pipes */

	/* Cria o pipe (dois descritores) e armazena seus valores no vetor
	 * fda. Agora: fda[0] para ler, fda[1] para escrever. Testa se deu
	 * erro. */
	if (pipe(fda) == -1) {
		erro("Criando pipe");
	}

	/* Imprime os valores na tela. Acompanhe: como não existe nenhum
	 * outro arquivo aberto por este processo, só os três que são
	 * padrões: stdin, stdout e stderr, ele deve assumir os próximos
	 * disponíveis: 3 e 4. */

	fprintf(stderr, "%d %d\n", fda[0], fda[1]);

	/* Agora o processo é dividido em dois pelo fork. Estudar o fork
	 * não é objetivo deste exemplo. Para isso, veja código do programa
	 * forki.c , do mesmo autor. */

	switch (fork()) {
	case -1:
		erro("fork");
		break;
	case 0:
		close(1);	/* ver *1a */
		dup(fda[1]);
		close(fda[1]);
		close(fda[0]);
		execlp("ls", "ls", 0);	/* ver *1b */
		erro("Voltou do ls");
		break;
	default:
		close(0);	/* ver *2a */
		dup(fda[0]);
		close(fda[0]);
		close(fda[1]);
		execlp("wc", "wc", 0);	/* ver *2b */
		erro("Voltou do wc");
		break;
	}
}
