#include <stdio.h> 
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <utime.h>
#include <libgen.h>
#include <pwd.h>
#include <stdbool.h>

#define LOG_FILE "/log_file.txt"
#define FILE_DROP_DIR "/file_drop"
#define MAX_FILE_NAME_LEN 1000


int intro()
{
    fprintf(stdout, "\n");
    for(int i = 0; i < 80; i++)
    {
        fprintf(stdout, "*");
    }
    fprintf(stdout, "\n\n");
    fprintf(stdout, "       #                            #####\n");
    fprintf(stdout, "      # #   #    # #####  ####     #     # #####    ##   #####  ###### #####\n");
    fprintf(stdout, "     #   #  #    #   #   #    #    #       #    #  #  #  #    # #      #    #\n");
    fprintf(stdout, "    #     # #    #   #   #    #    #  #### #    # #    # #    # #####  #    #\n");
    fprintf(stdout, "    ####### #    #   #   #    #    #     # #####  ###### #    # #      #####\n");
    fprintf(stdout, "    #     # #    #   #   #    #    #     # #   #  #    # #    # #      #   #\n");
    fprintf(stdout, "    #     #  ####    #    ####      #####  #    # #    # #####  ###### #    #\n");
    fprintf(stdout, "\n\n");
    for(int i = 0; i < 80; i++)
    {
        fprintf(stdout, "*");
    }
    fprintf(stdout, "\n\n");
    return (EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    int i;
    int rfd; //read file descripter
    int wfd; //write file descripter
    int fileCount; //number of files to copy, should only be one.
    int command; //variable used for switch for command line arguments.
    char wfile_name[PATH_MAX]; //name of the file to be copied.
    char wfile_drop_dir[PATH_MAX]; //location of the file drop directory.
    char wlog_file[PATH_MAX]; //location of the log file.
    char buf[1000]; //character buffer.
    ssize_t num_read; //number of bytes read for the file.
    ssize_t num_written; //number of bytes written for the file.
    FILE *lfp; //log file pointer.
    time_t rawtime; //raw time variable.
    struct tm *timeinfo; //a struck used to store time information for the new files.
    struct passwd *pwuid; //a struck used to store information about the present working user.
    struct utimbuf new_times; //a struck used to store new access and modified time information for the copied files.
    bool verbose = false; //variable used for command line arguments to set verbose mode.
    bool fastLoad = false; //variable used for command line arguments to set fastLoad mode.
    bool about = false; //variable used for command line arguments to show the about information.
    bool lisence = false; //variable used for command line arguments to show the lisencing information.
    struct stat rsb;
    struct stat wsb;
    time ( &rawtime ); //get the raw time.
    new_times.actime = time ( &rawtime ); //set the access time.
    new_times.modtime = time ( &rawtime ); //set the modified time.
    timeinfo = localtime ( &rawtime ); //set the time information based of the raw time of when this program was initialized.
    
    fileCount = 0;
    while((command = getopt(argc, argv, "alfvh")) != -1)
    {
        switch(command)
        {   
            case 'a':
                about = true;
                break;
            case 'l':
                lisence = true;
                break;
            case 'f':
                fastLoad = true;
                break;
            case 'v':
                verbose = true;
                break;
            case 'h':
                help = true;
                break;
            case '?':
                break;
        }
    }

    pwuid = getpwuid(geteuid()); //get the present working user id from the effective user id.
    memset(wfile_drop_dir, 0, PATH_MAX);
    strncpy(wfile_drop_dir, pwuid->pw_dir, PATH_MAX);
    strncat(wfile_drop_dir, FILE_DROP_DIR, 100);
    if(verbose)
    {
        fprintf(stdout, "%s\n", wfile_drop_dir); //if verbose print to console the directory to which the files are being copied.
    }
    memset(wlog_file, 0, PATH_MAX);
    strncpy(wlog_file, pwuid->pw_dir, PATH_MAX);
    strncat(wlog_file, LOG_FILE, 100);
    if(verbose)
    {
        fprintf(stdout, "%s\n", wlog_file); //if verbose print to console the log file name.
        printf("args %d\n", argc); //if verbose print to console the number of command line argument contain by argc.
    }
    lfp = fopen(wlog_file, "a" ); //open the log file in append mode.
    
//this needs to be modified to work with the command line arg stuff.
//    for (i = 1; i < argc; i++)
//    {
        if ((rfd = open(argv[argc], O_RDONLY)) > 0)
        {
            memset(wfile_name, 0, PATH_MAX);
            strncpy(wfile_name, wfile_drop_dir, PATH_MAX);
            strncat(wfile_name, "/", 100);
            strncat(wfile_name, argv[argc], 100);
            if (fstat(rfd, &rsb) == -1)
            {
                perror("stat");
                exit(EXIT_FAILURE);
            }
            if(verbose)
            {
                printf("File type:                ");
                switch (rsb.st_mode & S_IFMT)
                {
                    case S_IFBLK:  printf("block device\n");            break;
                    case S_IFCHR:  printf("character device\n");        break;
                    case S_IFDIR:  printf("directory\n");               break;
                    case S_IFIFO:  printf("FIFO/pipe\n");               break;
                    case S_IFLNK:  printf("symlink\n");                 break;
                    case S_IFREG:  printf("regular file\n");            break;
                    case S_IFSOCK: printf("socket\n");                  break;
                    default:       printf("unknown?\n");                break;
                }

                printf("I-node number:            %ld\n", (long) rsb.st_ino);
                printf("Mode:                     %lo (octal)\n", (unsigned long) rsb.st_mode);
                printf("Link count:               %ld\n", (long) rsb.st_nlink);
                printf("Ownership:                UID=%ld   GID=%ld\n", (long) rsb.st_uid, (long) rsb.st_gid);
                printf("Preferred I/O block size: %ld bytes\n", (long) rsb.st_blksize);
                printf("File size:                %lld bytes\n", (long long) rsb.st_size);
                printf("Blocks allocated:         %lld\n", (long long) rsb.st_blocks);
                printf("Last status change:       %s", ctime(&rsb.st_ctime));
                printf("Last file access:         %s", ctime(&rsb.st_atime));
                printf("Last file modification:   %s", ctime(&rsb.st_mtime));
            }
            if(verbose)
            {
                printf("File %d <%s>\n", i, wfile_name);
            }
            if ((wfd = open(wfile_name, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR)) > 0)
            {
                printf("  Beginning %s\n", wfile_name);
                printf("  Copying File: ");
                for ( ; ; )
                {
                    num_read = read(rfd, buf, sizeof(buf));
                    printf("****");
                    if(!fastLoad)
                    {
                        sleep(1);
                        fflush(stdout);
                    }
                    if (num_read > 0)
                    {
                        num_written = write(wfd, buf, num_read);
                        if (num_read != num_written)
                        {
	      // Houston, we have a problem!
                            perror("read/write mismatch ");
                            break;
                        }
                    }
                    else if (0 == num_read)
                    {
                        printf(" Complete\n  Done with %s\n", wfile_name);
                        fprintf(lfp, "Submitted %s @ %s", basename(wfile_name), asctime (timeinfo) );
                        fprintf(stdout, "\n");
                        for(int i = 0; i < 80; i++)
                        {
                            fprintf(stdout, "*");
                        }
                        break;
                    }
                    else
                    {
                        perror("could not read file");
                        break;
                    }
                }

                utime(wfile_name, &new_times);

                if (fstat(wfd, &wsb) == -1)
                {
                    perror("stat");
                    exit(EXIT_FAILURE);
                }
                if(verbose)
                {
                    printf("File type:                ");

                    switch (wsb.st_mode & S_IFMT)
                    {
                        case S_IFBLK:  printf("block device\n");            break;
                        case S_IFCHR:  printf("character device\n");        break;
                        case S_IFDIR:  printf("directory\n");               break;
                        case S_IFIFO:  printf("FIFO/pipe\n");               break;
                        case S_IFLNK:  printf("symlink\n");                 break;
                        case S_IFREG:  printf("regular file\n");            break;
                        case S_IFSOCK: printf("socket\n");                  break;
                        default:       printf("unknown?\n");                break;
                    }
                    printf("I-node number:            %ld\n", (long) wsb.st_ino);
                    printf("Mode:                     %lo (octal)\n", (unsigned long) wsb.st_mode);
                    printf("Link count:               %ld\n", (long) wsb.st_nlink);
                    printf("Ownership:                UID=%ld   GID=%ld\n", (long) wsb.st_uid, (long) wsb.st_gid);
                    printf("Preferred I/O block size: %ld bytes\n", (long) wsb.st_blksize);
                    printf("File size:                %lld bytes\n", (long long) wsb.st_size);
                    printf("Blocks allocated:         %lld\n", (long long) wsb.st_blocks);
                    printf("Last status change:       %s", ctime(&wsb.st_ctime));
                    printf("Last file access:         %s", ctime(&wsb.st_atime));
                    printf("Last file modification:   %s", ctime(&wsb.st_mtime));
                }
                close(wfd);
            }
            else
            {
                printf("***ERROR could not open <%s>\n", wfile_name);
                perror("could not open file to write");
            }
            close(rfd);
        }
        else
        {
            printf("***ERROR could not open <%s>\n", argv[i]);
            perror("could not open file to read");
        }
//    }
    fclose(lfp);
  return(EXIT_SUCCESS);
}
