#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
	char *line = NULL;
	char buf[20] = "";
	char * const a[1] = {NULL};
	char * const b[2] = {NULL, NULL};
	size_t linecapp = 0;
	
	getlogin_r(buf, 20);
	while(1){
		printf("%s => ", buf);
		getline(&line, &linecapp, stdin);
		pid_t pid = fork();

		if(pid == 0){ //child
			printf("%d", strcmp(line, "date\n"));
			if (strcmp(line, "date\n") == 0){
				execve("./date.sh", b, a);
		}
		} else if (pid > 0) { // parent
			wait();
		}  else { // fork failed
			printf("fork() failed!\n");
        return 1;
    }


			
			
		}

 return 0;
 
}

