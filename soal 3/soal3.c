#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <dirent.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    int pipp[2];
    int pipp_2[2];
    int status;
    pid_t child_1;
    pipe(pipp_2);
    child_1 = fork();
    if (child_1 == 0){
        pid_t child_2;
        pipe(pipp);
        child_2 = fork();
        if (child_2 == 0){
            pid_t child_3;
            child_3 = fork();
            if (child_3 == 0){
                char *argv[3] = {"unzip", "campur2.zip", NULL};
                execv("/usr/bin/unzip", argv);
            }else{
                while((wait(&status)) > 0);
                dup2(pipp[1], STDOUT_FILENO);
                close(pipp[0]);
                char *argv2[3] = {"ls", "campur2/", NULL};
                execv("/bin/ls", argv2);
            }
        }else{
            while((wait(&status)) > 0);
            dup2(pipp[0], STDIN_FILENO);
            dup2(pipp_2[1], STDOUT_FILENO);
            close(pipp[1]);
            close(pipp_2[0]);
            char *argv2[3] = {"grep", ".txt$", NULL};
            execv("/bin/grep", argv2);
        }
    }else{
        while((wait(&status)) > 0);
        char buff[100000];
        close(pipp_2[1]);
        close(pipp[0]);
        close(pipp[1]);
        FILE *daftar = fopen("daftar.txt", "w");
        read(pipp_2[0], buff, 100000);
        fputs(buff, daftar);
        fclose(daftar);
        char *argv[3] = {"xdg-open", "daftar.txt", NULL};
        execv("/usr/bin/xdg-open", argv);
    }
    return 0;
}