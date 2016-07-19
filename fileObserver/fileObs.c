/******************************************
* File Name: fileObs.c
* Purpose: an iNotify file observer to
*          watch a directory and send a
*          message to a (pipe?)
* Creation Date: 06-21-2016
* Last Modified: Wed 13 Jul 2016 02:32:34 PM PDT
* Created By: Jacob Shanklin
*******************************************/
#include <sys/inotify.h>
#include <limits.h>
//#include "fileObs.h"
#include "../TLPI/tlpi_hdr.h"
#include <sys/socket.h>
#include <time.h>
    
static void
displayInotifyEvent(struct inotify_event *i)
{
    FILE * fp;
    if (i->mask & IN_MOVED_TO && i->len > 0)
    {
	fp = fopen( "logfile.txt", "a" );
        int sockfd;
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
        sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
        if(sockfd != -1)
        {
            fprintf(fp, "LOG: %s, ENTRY TIME: %s\n", i->name, asctime (timeinfo));
            fprintf(stderr, "THIS WILL BE A MESSAGE ON A SOCKET. SOCKFD: %d\n", sockfd);
            //fprintf(sockfd, "%s", i->name); //print the filename to the UDP Sock
            //close UDP Socket
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
