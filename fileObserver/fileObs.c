/******************************************
* File Name: fileObs.c
* Purpose: an iNotify file observer to
*          watch a directory and send a
*          message to a (pipe?)
* Creation Date: 06-21-2016
* Last Modified: Wed 07 Sep 2016 11:07:22 AM PDT
* Created By: Jacob Shanklin
*******************************************/
#include <sys/inotify.h>
#include <limits.h>
//#include "fileObs.h"
#include "../lib/tlpi_hdr.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <sys/un.h>
#include <time.h>
#define SOCK_PATH "observer_socket"
#define MAX_MESSAGE_LENGTH 256
static void
displayInotifyEvent(struct inotify_event *i)
{
    FILE * fp;
    fprintf(stderr, "Caught: %d, need: %d\n", i->mask, IN_MOVED_TO);
    if (i->mask & IN_MOVED_TO && i->len > 0)
    {
	    //move and extract file to new location
        char studentName[MAX_STUDENT_NAME_LENGTH];
        char studentLab[2];
        char studentClass[7];
        char studentSection[8];

        studentClass = strtok(i->name, "+");
        studentSection = strtok(i->name, "+");
        studentLab = strtok(i->name, "+");
        studentName = strtok(i->name, ".tar");
        //Send required information to system TEST
        
        fp = fopen( "logfile.txt", "a" );
        int sockfd;
	    time_t rawtime;
        struct sockaddr_un sockAddr;
        int sockLen;
	    struct tm * timeinfo;
        int wlen;
        char message[MAX_MESSAGE_LENGTH];
	    memset(message, 0, sizeof(message));
        time ( &rawtime );
	    timeinfo = localtime ( &rawtime );
        sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
        fprintf(stderr, "Socket Open\n");
        if(sockfd != -1)
        {
            memset(&sockAddr, 0, sizeof(sockAddr));
            sockAddr.sun_family = AF_UNIX;
            strcpy(sockAddr.sun_path, SOCK_PATH);
            sockLen = strlen(sockAddr.sun_path) + sizeof(sockAddr.sun_family);
            if (connect(sockfd, (struct sockaddr *)&sockAddr, sockLen) == -1) {
                perror("Could not connect");
                exit(EXIT_FAILURE);
            }
            
            fprintf(fp, "LOG: %s, ENTRY TIME: %s\n", i->name, asctime (timeinfo));
            
            strncpy(message, i->name, MAX_MESSAGE_LENGTH-1); //print the filename to the UDP Sock
            wlen = write(sockfd, message, strlen(i->name));
            fprintf(stderr, ">>%s<<\nBytes written: >>%d<<\nSTRLEN: >>%d<<\n", message, wlen, (int)strlen(message));
            close(sockfd);
        }
	fclose(fp);
    }


}

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))
#define watchDir "../test"

int main(int argc, char *argv[])
{
    int inotifyFd, wd; //file disc for the new file
    char buf[BUF_LEN] __attribute__ ((aligned(8)));
    ssize_t numRead;
    char *p;
    struct inotify_event *event;

    inotifyFd = inotify_init();
    if (inotifyFd == -1)
        errExit("inotify_init");

    wd = inotify_add_watch(inotifyFd, watchDir, IN_ALL_EVENTS);
    if (wd == -1)
        errExit("inotify_add_watch");

    printf("Watching %s using wd %5d\n", watchDir, wd);

    for(;;) {
        numRead = read(inotifyFd, buf, BUF_LEN);
        fprintf(stderr, "Read a file event");
        if(numRead == 0)
            fatal("read() from inotify fd return 0!");

        if (numRead == -1)
            errExit("read");
        
        for (p = buf; p < buf + numRead; ) {
            event = (struct inotify_event *) p;
            displayInotifyEvent(event);

            p += sizeof(struct inotify_event) + event->len;
        }
    }

    exit(EXIT_SUCCESS);;
}
