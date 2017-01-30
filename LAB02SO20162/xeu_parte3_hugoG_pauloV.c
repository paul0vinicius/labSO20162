#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>


#define USERNAME_SIZE 20


void clean_out(){
	FILE *arq;
	arq = fopen("out.txt", "w+");
	fclose(arq);
}

void clean_log(){
	FILE *arq;
	arq = fopen("log.txt", "w+");
	fclose(arq);
	char *head = "index || programa_e_args || pid || uid || gid || start_epoch || end_epoch || return_value\n";
	escrita(head);
}

int escreve_saida(){
	FILE *arq;
  	char Linha[100];
  	char *result;
  	int i;
  	arq = fopen("out.txt", "a+");
  	if (arq == NULL) {  // Se houve erro na abertura 
     	printf("Problemas na abertura do arquivo\n");
     	return -1;
  	}
    result = fgets(Linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
    if(result){
    	printf("%s", result);
    	escrita(result);
	} else{
		escrita("\n");
	}
	clean_out();

}

int escrita(char *param){
	int result;
	char Str[100];
	FILE *arq;
	arq = fopen("log.txt", "a+");  // Cria um arquivo texto para gravação

	if (arq == NULL) {
		printf("Problemas na CRIACAO do arquivo\n");
   		return -1;
   	}

   	strcpy(Str,param);
	result = fputs(Str, arq);

	if (result == EOF)
    	printf("Erro na Gravacao\n");
 	fclose(arq);

 }

 int leitura(){
	FILE *arq;
  	char Linha[100];
  	char *result;
  	int i;
  	arq = fopen("log.txt", "a+");

  	if (arq == NULL) {  // Se houve erro na abertura 
     	printf("Problemas na abertura do arquivo\n");
     	return -1;
  	}
  	i = 1;
    result = fgets(Linha, 100, arq);
    printf("%s\n", Linha);
  	while (!feof(arq)) { // Lê uma linha (inclusive com o '\n')
      	result = fgets(Linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
      	if (result)
	  		printf("%d || %s\n",i, Linha);
      	i++;
  	}
  	fclose(arq);
    clean_out();
    exit(EXIT_SUCCESS);

   }


int main() {
	clean_log();

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
    int track_flag = 0;

    time_t start_t, end_t;

	pid_t w;
    int status;
	username = getenv("USER");
	while(true){
		char mem[256] = "";
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
		
		if (strcmp(p, "track") == 0){
			track_flag = 1;
		} else track_flag = 0;
		
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
		char x[15];
		if(pid == 0){ // Processo filho

			if(!track_flag){
			
				p = parameters[0];
				int a = 0;
				while(p != NULL){
					strcat(mem, p);
					strcat(mem, " ");
					a++;
					p = parameters[a];
				}
				if (pipe_flag){
					strcat(mem, "| ");
					p = parameters_2[0];
					int a = 0;
					while(p != NULL){
						strcat(mem, p);
						strcat(mem, " ");
						a++;
						p = parameters_2[a];
					}
				}

				strcat(mem, "|| ");

				sprintf(x, "%d", getpid());
				strcat(mem, x);
				strcat(mem, " || ");

				sprintf(x, "%d", getuid());
				strcat(mem, x);
				strcat(mem, " || ");

				sprintf(x, "%d", getpgid(pid));
				strcat(mem, x);
				strcat(mem, " || ");

				time(&start_t);
				sprintf(x, "%ld", start_t);
				strcat(mem, x);
				strcat(mem, " || ");

				escrita(mem);
			}

			if (!pipe_flag){
				if (track_flag){
					leitura();
				}
				if (pipe(pipefd) == -1) {
        			perror("pipe");
        			exit(EXIT_FAILURE);
        		}
        		clean_out();

				int fd = open("out.txt", O_RDWR);
	        	dup2(fd, 1);

				execvp(parameters[0], parameters);

        		close(fd);
							
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

			if (!track_flag){
				printf("Comando não encontrado!\n");
				exit(EXIT_FAILURE);
			}
			
		} else if (pid > 0) { // Processo pai
		    w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
            if (w == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
          	if (WIFEXITED(status)) {
           		time(&end_t);
				if (!track_flag){
					sprintf(x, "%ld", end_t);
					strcat(mem, x);
					strcat(mem, " || ");
					escrita(mem);
					escreve_saida();
				}
            } 
			wait(NULL);
		} else{ // Falha na criação do Fork
			printf("fork() failed!\n");
        	return -1;
		}
	}

 return 0;
 
}

