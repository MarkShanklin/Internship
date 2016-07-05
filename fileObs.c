/******************************************
* File Name: fileObs.c
* Purpose: an iNotify file observer to
*          watch a directory and send a
*          message to a (pipe?)
* Creation Date: 06-21-2016
* Last Modified: Mon 27 Jun 2016 02:23:22 PM PDT
* Created By: Jacob Shanklin
*******************************************/
#include <sys/inotify.h>
#include <limits.h>
#include "fileObs.h"
static void
displayInotifyEvent(struct inotify_event *i)
{
    if (i->mask & IN_MOVED_TO && i->len > 0)
    {
        int sockfd;
        sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
        //open a UDP Socket on sock
        fprintf(sock, "%s", i->name); //print the filename to the UDP Sock
        //close UDP Socket
    }


}

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int main(int argc, char *argv[])
{
    int inotifyFd, wd, j; //file disc for the new file
    char buf[BUF_LEN] __attribute__ ((aligned(8)));
    ssize_t numRead;
    char *p;
    struct inotify_event *event;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
            usageErr("%s pathname...\n", argv[0]);

    inotifyFd = inotify_init();
    if (inotifyFd == -1)
        errExit("inotify_init");

    for (j = 1; j < argc; j++) 
    {
        wd = inotify_add_watch(inotifyFd, argv[j], IN_ALL_EVENTS);
        if (wd == -1)
            errExit("inotify_add_watch");

        printf("Watching %s using wd %5d\n", argv[j], wd);
    }

    for(;;) {
        numRead = read(inotifyFd, buf, BUF_LEN);
        if(numRead == 0)
            fatal("read() from inotify fd return 0!");

        if (numRead == -1)
            errExit("read");

        printf("read %ld bytes from inotify fd\n", (long) numRead);

        for (p = buf; p < buf + numRead; ) {
            event = (struct inotify_event *) p;
            displayInotifyEvent(event);

            p += sizeof(struct inotify_event) + event->len;
        }
    }

    exit(EXIT_SUCCESS);;
}
