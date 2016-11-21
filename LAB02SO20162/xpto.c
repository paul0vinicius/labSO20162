#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
char * const a[1] = {NULL};
char * const b[2] = {NULL, NULL};

execve("./date.sh", b, a);

return 0;
}
