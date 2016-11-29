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
			
		int i = 0;
		int j = 0;
		while(p != NULL){
			if (strcmp(p, "|") == 0){
				pipe_flag = true;
				p = strtok(NULL, " \n\0");
				while(p != NULL){
					parameters_2[j] = p;
					printf("parametro2:%s\n", parameters_2[j]);
					j++;
					p = strtok(NULL, " \n\0");
				}
				parameters[j] = NULL;
			}else{
				parameters[i] = p;
				printf("parametro1:%s\n", parameters[i]);
				i++;
				p = strtok(NULL, " \n\0");
			}
			
		}

		// O último parâmetro do array deve ser nulo, por isso, ao sair do array, o null é inserido.
		parameters[i] = NULL;	
		
		pid_t pid = fork();
		
		if(pid == 0){ // Processo filho
			
			if (!pipe_flag){
				//strcat(path, parameters[0]);
				execvp(parameters[0], parameters);
				//execve(path, parameters, envp);
			} else {
				if (pipe(pipefd) == -1) {
		        perror("pipe");
		        exit(EXIT_FAILURE);
    		}
				pid_t pid_pipe = fork();

				if(pid_pipe == 0) {
					pipe_flag = false;
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
					//wait(NULL);
				} else return -1;
			}

			printf("Comando não encontrado!\n");
			while (i >= 0) {
				printf("%d\n", i);
				parameters[i] = NULL;
				i--;
			}
			while (j >= 0) {
				printf("%d\n", j);
				parameters_2[j] = NULL;
				j--;
			}
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

