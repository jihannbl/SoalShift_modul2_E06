#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

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

        if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

int counter = 1;
while(1) {

	struct stat makan;
	stat("/home/jihan/Documents/makanan/makan_enak.txt", &makan);
	time_t waktu_file = makan.st_atime;
	time_t waktu_now = time(NULL);

	double rangew = difftime(waktu_now, waktu_file);

	if(rangew >= 0 && rangew <= 30)
	{
		pid_t child = fork();
		int status = 0;
		char namafile[20];
                chdir("/home/jihan/Documents/makanan");
		if (child == 0){
		 sprintf(namafile, "makan_sehat%d.txt", counter);
		 char *argv[3] = {"touch", namafile, NULL};
		 execv("/usr/bin/touch", argv);
		}
		else {
		 while((wait(&status)) > 0);
		 counter++;
		}
//		counter++;
	}
	sleep(5);
     }
	exit(EXIT_SUCCESS);
}
