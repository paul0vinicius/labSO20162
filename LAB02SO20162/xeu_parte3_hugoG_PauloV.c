#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIZE_USERNAME 20

int main() {
	typedef enum {false, true} bool;

	char *line = NULL;
	char username[MAX_SIZE_USERNAME] = "";
	//char *name = NULL;
	char *parameters[] = {};
	char *system_variables[] = {};
	size_t linecapp = 0;
	bool pipe = false;
	int pipefd[2];
	char buf;

	// Explicação mais clara do que é o argumento 0 do array de parâmetros.
	//char *command = *parameters[0];

	
	while(1){
		getlogin_r(username, MAX_SIZE_USERNAME);
		//name = getlogin();
		printf("%s => ", username);
		getline(&line, &linecapp, stdin);
		
		pid_t pid = fork();
		
		if(pid == 0){ //child

			// Modularizar isso para uma função - Split
			char *p = strtok(line, " ");
			
			int i = 0;
			while(p != NULL){
				parameters[i] = p;
				i++;
				p = strtok(NULL, " ");
			}
			//

			// Será que tem como transformar em um case?
			if (strcmp(parameters[0], "date\n") == 0){
				execve("./programs/date.sh", parameters, system_variables);
			} else if (strcmp(parameters[0], "sleep") == 0){
				execve("./programs/sleep.sh", parameters, system_variables);
			} else if ((strcmp(parameters[0], "ls")) == 0 || (strcmp(parameters[0], "ls\n")) == 0){
				execve("./programs/ls.sh", parameters, system_variables);
			} else if ((strcmp(parameters[0], "grep")) == 0){
				execve("./programs/grep.sh", parameters, system_variables);
			} else if ((strcmp(parameters[0], "pipe")) == 0){
				pipe = true;
				close(pipefd[1]);          /* Close unused write end */
				while (read(pipefd[0], &buf, 1) > 0) write(STDOUT_FILENO, &buf, 1);
				write(STDOUT_FILENO, "\n", 1);
				close(pipefd[0]);
				_exit(EXIT_SUCCESS);
			} 
			else printf("Command not found\n");

			// Modularizar isso para uma função - Limpeza do array de parâmetros após a leitura
			// int j = 0;
			// while(j < i){
			// 	parameters[j] = NULL;
			// 	j++;
			// }
			//

			_exit(EXIT_SUCCESS);
		
		}else if (pid > 0) { // parent
			if (pipe) {
				pipe = false;
				close(pipefd[0]);          /* Close unused read end */
				write(pipefd[1], parameters[3], strlen(parameters[3]));
				close(pipefd[1]);          /* Reader will see EOF */
				wait(NULL);                /* Wait for child */
				exit(EXIT_SUCCESS);
			} else wait(NULL);
		}else{ // fork failed
			printf("fork() failed!\n");
        	return 1;
		}
	}

 return 0;
 
}

