#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //usleep
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>

#include <inttypes.h>

#define ACCESS_PERMISSION 0777

int main (int argc, char* argv[]) {

    int fd;
    char pathbuf[256];
    char* path = argv[1];

    snprintf (pathbuf, sizeof pathbuf, "%s", path);
    fd = open (pathbuf, O_RDWR, ACCESS_PERMISSION);
    char* buf = (char*) malloc (sizeof (char) * 42);
    write (fd, buf, 42);
    sleep (30);

    return 0;
}
