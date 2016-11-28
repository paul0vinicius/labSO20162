#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define USERNAME_SIZE 20

int main() {
	typedef enum {false, true} bool;

	char *line = NULL;
	char username[USERNAME_SIZE] = "";
	char path[] = "/bin/";
	char *parameters[] = {NULL};
	size_t linecapp = 0;
	char *envp[] =
	{
		"HOME=/",
		"PATH=/bin:/usr/bin",
		"TZ=UTC0",
		"USER=paul0vinicius",
		NULL
    };
	
	while(true){
		getlogin_r(username, USERNAME_SIZE);
		printf("%s => ", username);
		getline(&line, &linecapp, stdin);
		
		pid_t pid = fork();
		
		if(pid == 0){ //child

			// Modularizar isso para uma função - Split
			char *p = strtok(line, " \n");
			
			int i = 0;
			while(p != NULL){
				parameters[i] = p;
				i++;
				p = strtok(NULL, " \n");
			}

			parameters[i] = NULL;
			//printf("%s\n", parameters);
			//

			// for (int j = i; j > 0; j--)
			// {
			// 	printf("%s\n", parameters[j]);
			// }

			strcat(path, parameters[0]);

			printf("%s\n", path);
			//printf("%s\n", parameters[1]);

			execve(path, parameters, envp);

			printf("Comando não encontrado!\n");
			_exit(EXIT_SUCCESS);

		} else if (pid > 0) { // parent
			wait(NULL);
		} else{ // fork failed
			printf("fork() failed!\n");
        	return 1;
		}
	}

 return 0;
 
}

