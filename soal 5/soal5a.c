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
#include <sys/wait.h>

int main() {
    pid_t pid, sid;

    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();

    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/home/kulguy/log/")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    int counter = 0;
    char namafolder[20];
    while(1) {
        counter %= 30;
        // printf("%d", counter);
        pid_t child;
        int status = 0;
        child = fork();
        if (counter == 0){
            time_t rawtime;
            struct tm * timeinfo;  
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            strftime(namafolder, 20, "%d:%b:%Y-%H:%M", timeinfo);
            if (child == 0){
                char *argv[4] = {"mkdir", "-p", namafolder, NULL};
                execv("/bin/mkdir", argv);
            }
            else{
                while((wait(&status)) > 0);
            }
        }else{
            char namafile[20];
            chdir(namafolder);
            if (child == 0){
                sprintf(namafile, "log%d.log",counter);
                char *argv[4] = {"cp", "/var/log/syslog", namafile, NULL};
                execv("/bin/cp", argv);
            }
            else{
                while((wait(&status)) > 0);
            }
        }
        sleep(60);
        counter++;
    }

    exit(EXIT_SUCCESS);
}