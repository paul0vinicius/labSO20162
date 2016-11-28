#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIZE_USERNAME 20

int main() {

char username[MAX_SIZE_USERNAME] = "";

getlogin_r(username, MAX_SIZE_USERNAME);

printf("%s\n", username);
}
