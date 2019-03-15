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
    system("rm -r campur2/");
    system("rm daftar.txt");
    int fd[2];
    int status;
    pid_t child_1;
    pipe(fd);
    child_1 = fork();
    if (child_1 == 0){
        pid_t child_2;
        child_2 = fork();
        if (child_2 == 0){
            pid_t child_3;
            child_3 = fork();
            if (child_3 == 0){
                char *argv[3] = {"unzip", "campur2.zip", NULL};
                execv("/usr/bin/unzip", argv);
            }else{
                while((wait(&status)) > 0);
                char *argv2[3] = {"touch", "daftar.txt", NULL};
                execv("/usr/bin/touch", argv2);
            }
        }else{
            while((wait(&status)) > 0);
            // dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            // char *argv[4] = {"ls", "campur2/", NULL};
            // execv("/bin/ls", argv);
            DIR *file;
            struct dirent *entry;
            file = opendir("campur2");
            // close(p[0]);
            if (file != NULL){
                while(entry = readdir(file)){
                    int len = strlen(entry->d_name);
                    char *extension = &entry->d_name[len - 4];
                    char namafile[1000];
                    strcpy(namafile, entry->d_name);
                    strcat(namafile, "\n");
                    if (strcmp(extension, ".txt") == 0){
                        write(fd[1], namafile, 1000);
                        // write(fd[1], "\n", 2);
                    }
                }
            }
            (void) closedir (file);  
        }
    }else{
        while((wait(&status)) > 0);
        // dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        char buffer[1000];
        FILE *fp = fopen("daftar.txt", "a+");
        while(read(fd[0], buffer, 1000)){
            int len = strlen(buffer);
            char *ext = &buffer[len - 4];
            fprintf(fp, "%s", buffer);
        }
        fclose(fp);
        char *argv[3] = {"xdg-open", "daftar.txt", NULL};
        execv("/usr/bin/xdg-open", argv);
    }
    return 0;
}