/******************************************
* File Name: fileObs.c
* Purpose: an iNotify file observer to
*          watch a directory and send a
*          message to a (pipe?)
* Creation Date: 06-21-2016
* Last Modified: Tue 21 Jun 2016 11:11:25 AM PDT
* Created By: Jacob Shanklin
*******************************************/
#include <sys/inotify.h>

int main(int argc, char *argv[])
{
    int loopCounter = 0;
    int fd; //file disc for the new file
    int pd; //file disc for the pipe? maybe use a UDP socket

    //create an iNotify event
    //add the /submissions directory to the watch list
    //create a message queue and send the message.

    return 0;
}
