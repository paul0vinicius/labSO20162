#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


// http://www.inf.ufrgs.br/~elgios/linux/programacao_C/pipe.c
int main () {
	char *parameters1[] = {"ps", "xau", NULL};
	char *parameters2[] = {"grep", "root", NULL};
	
	
	int pipefd[2];
    pid_t cpid;
    char buf;
	if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    cpid = fork();
    
	if (cpid == 0){
		close(1);
		dup(pipefd[1]);
		close(pipefd[1]);
		close(pipefd[0]);
		execvp(parameters1[0], parameters1);
	} else if (cpid > 0){
		close(0);	/* ver *2a */
		dup(pipefd[0]);
		close(pipefd[0]);
		close(pipefd[1]);
		execvp(parameters2[0], parameters2);
	} else return -1;
	
}
