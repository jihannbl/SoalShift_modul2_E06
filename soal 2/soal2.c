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
#include <pwd.h>
#include <grp.h>

int main(){
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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
	struct stat info;
    stat("/home/jihan/hatiku/elen.ku", &info);
    struct passwd *pwd = getpwuid(info.st_uid);
    struct group  *grp = getgrgid(info.st_gid);
         if ( strcmp(pwd->pw_name, "www-data") == 0 && strcmp(grp->gr_name, "www-data") == 0)
        {
          pid_t child = fork();
          int status = 0;
          if (child == 0){
            char *argv[4] = {"chmod", "777", "/home/jihan/hatiku/elen.ku", NULL};
            execv("/bin/chmod", argv);
           }
         else{
                while((wait(&status)) > 0);
                remove("/home/jihan/hatiku/elen.ku");
             }
        }
    sleep(3);
 }

  exit(EXIT_SUCCESS);
}
