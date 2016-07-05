/***********************************************************
* File Name     : get_num.h
* Purpose       : Functions for parsing numeric command-line arguments
* Creation Date : 06-28-2016
* Last Modified : Tue 28 Jun 2016 11:29:53 AM PDT
* Created By    : Mark Shanklin 
***********************************************************/

#ifndef GET_NUM_H
#define GET_NUM_H

#define GN_NONNEG       01      /* Value must be >= 0 */
#define GN_GT_0         02      /* Value must be > 0 */

                                /* By default, intergers are decimal */
#define GN_ANY_BASE     0100    /* Can use any base - line strtol(3) */
#define GN_BASE_8       0200    /* Value is expressed in octal */
#define GN_BASE_16      0400    /* Value is expressed in hexadecimal */

long getLong(const char *arg, int flags, const char *name);

int getInt(const char *arg, int flags, const char *name);

#endif
