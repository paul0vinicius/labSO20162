#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIZE_USERNAME 20

int main() {
	char *line = NULL;
	char username[MAX_SIZE_USERNAME] = "";
	char *parameters[] = {};
	char *system_variables[] = {};
	size_t linecapp = 0;

	//Verificar como definir esse babado aqui pra facilitar a leitura, etc
	char *command = *parameters[0];

	int i = 0;

	getlogin_r(username, MAX_SIZE_USERNAME);
	
	while(1){
		printf("%s => ", username);
		getline(&line, &linecapp, stdin);
		
		pid_t pid = fork();
		
		if(pid == 0){ //child

			// Modularizar isso para uma função
			char *p = strtok(line, " ");
		
			while(p != NULL){
				parameters[i] = p;
				i++;
				p = strtok(NULL, " ");
			}
			//

			// Será que tem como transformar em um case?
			if (strcmp(parameters[0], "date\n") == 0){
				execve("./date.sh", parameters, system_variables);
			} else if (strcmp(parameters[0], "sleep") == 0){
				execve("./sleep.sh", parameters, system_variables);
			} else printf("Command not found\n");

			// Modularizar isso para uma função
			int j = 0;
			while(j < i){
				parameters[j] = NULL;
				j++;
			}
			//
		
		}else if (pid > 0) { // parent
			wait();
		}else{ // fork failed
			printf("fork() failed!\n");
        	return 1;
		}
	}

 return 0;
 
}

