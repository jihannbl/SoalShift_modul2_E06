#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main(){
    char *argv[3] = {"pkill", "soal5a", NULL};
    execv("/usr/bin/pkill", argv);
    return 0;
}