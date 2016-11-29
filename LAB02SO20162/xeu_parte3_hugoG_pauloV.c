#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define USERNAME_SIZE 20

int main() {
	typedef enum {false, true} bool;

	char *line = NULL;
	char *username = NULL;
	char path[] = "/bin/";
	char *parameters[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
	char *parameters_2[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
	size_t linecapp = 0;
	char *envp[] =
	{
		"HOME=/",
		"PATH=/bin:/usr/bin",
		"TZ=UTC0",
		NULL
    };
    int pipefd[2];
    bool pipe_flag = false;

	username = getenv("USER");
	while(true){
		printf("%s => ", username);
		getline(&line, &linecapp, stdin);
		
		// Modularizar isso para uma função - Split
		char *p = strtok(line, " \n\0");
		
		// Limpeza dos arrays após captura dos parâmetros
		int i = 0;
		int j = 0;
		while (i < 8) {
			//printf("%d\n", i);
			parameters[i] = NULL;
			i++;
		}

		while (j < 8) {
			//printf("%d\n", j);
			parameters_2[j] = NULL;
			j++;
		}
		//

		// Split dos parâmetros nos arrays
		i = 0;
		j = 0;
		while(p != NULL){
			if (strcmp(p, "|") == 0){
				pipe_flag = true;
				p = strtok(NULL, " \n\0");
				while(p != NULL){
					parameters_2[j] = p;
					//printf("parametro2:%s\n", parameters_2[j]);
					j++;
					p = strtok(NULL, " \n\0");
				}
				parameters[j] = NULL;
			} else {
				pipe_flag = false;
				parameters[i] = p;
				//printf("parametro1:%s\n", parameters[i]);
				i++;
				p = strtok(NULL, " \n\0");
			}
			
		}
		//

		// O último parâmetro do array deve ser nulo, por isso, ao sair do array, o null é inserido.

		// O último parâmetro null do segundo array é inserido dentro do loop para evitar erros quando
		// este array não for utilizado.
		parameters[i] = NULL;	
		
		pid_t pid = fork();
		
		if(pid == 0){ // Processo filho
			
			if (!pipe_flag){
				execvp(parameters[0], parameters);
			} else {
				if (pipe(pipefd) == -1) {
		        perror("pipe");
		        exit(EXIT_FAILURE);
    		}
				pid_t pid_pipe = fork();

				if(pid_pipe == 0) {
					close(1);
					dup(pipefd[1]);
					close(pipefd[1]);
					close(pipefd[0]);
					execvp(parameters[0], parameters);
				} else if (pid_pipe > 0) {
					close(0);
					dup(pipefd[0]);
					close(pipefd[0]);
					close(pipefd[1]);					
					execvp(parameters_2[0], parameters_2);
				} else return -1;
			}

			printf("Comando não encontrado!\n");
			_exit(EXIT_FAILURE);
		} else if (pid > 0) { // Processo pai
			wait(NULL);
		} else{ // Falha na criação do Fork
			printf("fork() failed!\n");
        	return -1;
		}
	}

 return 0;
 
}

