#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define USERNAME_SIZE 20


int escrita(char *param){
	//FILE *arq;
	int result;
	//char Str[50];
	//arq = fopen("log.txt", "rt");

	char Str[100];
	FILE *arq;

	arq = fopen("log.txt", "a+");  // Cria um arquivo texto para gravação
	if (arq == NULL) // Se não conseguiu criar
	{
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
  // Abre um arquivo TEXTO para LEITURA
  	arq = fopen("log.txt", "a+");
  	if (arq == NULL) {  // Se houve erro na abertura 
     	printf("Problemas na abertura do arquivo\n");
     	return -1;
  	}
  	i = 1;
  	while (!feof(arq)) { // Lê uma linha (inclusive com o '\n')
      	result = fgets(Linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
      	if (result)  // Se foi possível ler
	  	printf("%d : %s\n",i,Linha);
      	i++;
  	}
  	fclose(arq);
   }


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
    int track_flag = 0;

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
		}
		
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
			strcat(mem,line);
			strcat(mem, " || ");

			char x[10];
			sprintf(x, "%d", getpid());
			strcat(mem, x);
			strcat(mem, " || ");

			sprintf(x, "%d", getuid ());
			strcat(mem, x);
			strcat(mem, " || ");

			sprintf(x, "%d", getpgid(pid));
			strcat(mem, x);
			strcat(mem, " || \n");

			escrita(mem);

			if (!pipe_flag){
				if (track_flag)
					leitura();
				if (pipe(pipefd) == -1) {
        			perror("pipe");
        			exit(EXIT_FAILURE);
        		}
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

