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
	char *parameters[] = {NULL};
	size_t linecapp = 0;
	char *envp[] =
	{
		"HOME=/",
		"PATH=/bin:/usr/bin",
		"TZ=UTC0",
		NULL
    };

	username = getenv("USER");
	while(true){
		printf("%s => ", username);
		getline(&line, &linecapp, stdin);
		
		pid_t pid = fork();
		
		if(pid == 0){ // Processo filho

			// Modularizar isso para uma função - Split
			char *p = strtok(line, " \n");
			
			int i = 0;
			while(p != NULL){
				parameters[i] = p;
				i++;
				p = strtok(NULL, " \n");
			}

			// O último parâmetro do array deve ser nulo, por isso, ao sair do array, o null é inserido.
			parameters[i] = NULL;

			strcat(path, parameters[0]);
			execve(path, parameters, envp);

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

