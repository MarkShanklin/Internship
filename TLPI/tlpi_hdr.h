/***********************************************************
* File Name     : TLPI_hdr.h
* Purpose       : The Linux Programmer Interface Header File
* Creation Date : 06-28-2016
* Last Modified : Tue 28 Jun 2016 11:17:50 AM PDT
* Created By    : Mark Shanklin 
***********************************************************/

#ifndef TLPI_HDR_H
#define TLPI_HDR_H      /* Prevent accidental double inclusion */

#include <sys/types.h>  /* Type definitions used by many programs */
#include <stdio.h>      /* Standard I/O functions */
#include <stdlib.h>     /* Prototypes of commonly used library functions,
                           plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for may system calls */
#include <errno.h>      /* Declares errno and defines error constants */
#include <string.h>     /* Commonly used string-handling functions */

#include "get_num.h"    /* Declares out functions for handling numeric
                           arguments (getInt(), getLong()) */

#include "error_functions.h"    /* Declares our error-handling functions */

typedef enum { FALSE, TRUE } Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

#endif