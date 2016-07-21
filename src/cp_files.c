#include <stdio.h> 
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <libgen.h>

// You want to replace this with some code that calls
// struct passwd *getpwuid(uid_t uid);
#define FILE_DROP_DIR "/home/grader_dev/file_drop"
#define LOG_FILE "/home/grader_dev/file_drop/log_file.txt"
int main(int argc, char *argv[])
{
  int i;
  int rfd;
  int wfd;
  char wfile_name[PATH_MAX];
  char buf[1000];
  ssize_t num_read;
  ssize_t num_written;
  FILE *lfp;
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  printf("args %d\n", argc);
  lfp = fopen(LOG_FILE, "a" );

  for (i = 1; i < argc; i++) {
    if ((rfd = open(argv[i], O_RDONLY)) > 0) {
      memset(wfile_name, 0, PATH_MAX);
      strncpy(wfile_name, FILE_DROP_DIR, PATH_MAX);
      strncat(wfile_name, "/", 100);
      strncat(wfile_name, argv[i], 100);
      printf("file %d <%s>\n", i, wfile_name);
      if ((wfd = open(wfile_name, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR)) > 0) {
	printf("  beginning %s\n", wfile_name);
	for ( ; ; ) {
	  num_read = read(rfd, buf, sizeof(buf));
	  if (num_read > 0) {
	    num_written = write(wfd, buf, num_read);
	    if (num_read != num_written) {
	      // Houston, we have a problem!
	      perror("read/write mismatch ");
	      break;
	    }
	  }
	  else if (0 == num_read) {
	    printf("  done with %s\n", wfile_name);
	    fprintf(lfp, "submitted %s @ %s", basename(wfile_name), asctime (timeinfo) );
	    break;
	  }
	  else {
	    perror("could not read file");
	    break;
	  }
	}
	close(wfd);
      }
      else {
	printf("***ERROR could not open <%s>\n", wfile_name);
	perror("could not open file to write");
      }
      close(rfd);
    }
    else {
      printf("***ERROR could not open <%s>\n", argv[i]);
      perror("could not open file to read");
    }
  }
  fclose(lfp);
  return(0);
}
