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
#include <pwd.h>

#define LOG_FILE "/log_file.txt"
#define FILE_DROP_DIR "/file_drop"

int main(int argc, char *argv[])
{
  int i;
  int rfd;
  int wfd;
  char wfile_name[PATH_MAX];
  char wfile_drop_dir[PATH_MAX];
  char wlog_file[PATH_MAX]; 
  char buf[1000];
  ssize_t num_read;
  ssize_t num_written;
  FILE *lfp;
  time_t rawtime;
  struct tm *timeinfo;
  struct passwd *pwuid;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  pwuid = getpwuid(geteuid());
  memset(wfile_drop_dir, 0, PATH_MAX);
  strncpy(wfile_drop_dir, pwuid->pw_dir, PATH_MAX);
  strncat(wfile_drop_dir, FILE_DROP_DIR, 100);
  fprintf(stdout, "%s\n", wfile_drop_dir);
 
  memset(wlog_file, 0, PATH_MAX);
  strncpy(wlog_file, pwuid->pw_dir, PATH_MAX); 
  strncat(wlog_file, LOG_FILE, 100);
  fprintf(stdout, "%s\n", wlog_file);
  printf("args %d\n", argc);
  lfp = fopen(wlog_file, "a" );

  for (i = 1; i < argc; i++) {
    if ((rfd = open(argv[i], O_RDONLY)) > 0) {
      memset(wfile_name, 0, PATH_MAX);
      strncpy(wfile_name, wfile_drop_dir, PATH_MAX);
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
