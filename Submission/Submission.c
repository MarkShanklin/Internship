/***********************************************************
* File Name     : Submission.c
* Purpose       : Submission system for the Grading Environment
* Creation Date : 06-30-2016
* Last Modified : Wed 13 Jul 2016 11:51:04 AM PDT
* Created By    : Mark Shanklin 
***********************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <libgen.h>

#define MAX_FILE_NAME_LEN       50
#define MAX_CLASS_NAME_LEN      7
#define MAX_SECTION_NAME_LEN    9
#define MAX_LAB_NAME_LEN        5
#define MAX_USER_NAME_LEN       32

int main (int argc, char *argv[])
{
    int command = 0;
    int i = 0;
    int j = 0;
    
    char Class[MAX_CLASS_NAME_LEN];
    char Section[MAX_SECTION_NAME_LEN];
    char Lab[MAX_LAB_NAME_LEN];
    char User[MAX_USER_NAME_LEN];
    char FileName[MAX_FILE_NAME_LEN];
    
    while((command = getopt(argc,argv, "c:C:s:S:l:L:u:U:hH")) != -1)
    {
        
        switch(command)
        {
            case 'c':
            case 'C':
                optind--;
                for (i = optind; i < argc && (*argv[i] != '-'); i++)
                {
                    if (strlen(argv[i]) < MAX_CLASS_NAME_LEN)
                    {
                        strcpy(Class, argv[i]);
                        for(j = 0; Class[j]; j++)
                        {
                            Class[j] = tolower(Class[j]);
                        }
                    }
                }
                break;
            case 's':
            case 'S':
                optind--;
                for (i = optind; i < argc && (*argv[i] != '-'); i++)
                {
                    if (strlen(argv[i]) < MAX_SECTION_NAME_LEN)
                    {
                        strcpy(Section, "section");
                        strcat(Section, argv[i]);
                    }
                }
                break;
            case 'l':
            case 'L':
                optind--;
                for (i = optind; i < argc && (*argv[i] != '-'); i++)
                {
                    if (strlen(argv[i]) < MAX_LAB_NAME_LEN)
                    {
                        strcpy(Lab, "lab");
                        strcat(Lab, argv[i]);
                    } 
                }
                break;
            case 'u':
            case 'U':
                optind--;
                for (i = optind; i < argc && (*argv[i] != '-'); i++)
                {
                    if (strlen(argv[i]) < MAX_USER_NAME_LEN)
                    {
                        strcpy(User, argv[i]);
                        for (j = 0; User[j]; j++)
                        {
                            User[j] = tolower(User[j]);
                        }
                    }
                }
                break;
            case 'h':
            case 'H':
                
                break;
            case '?':
                break;
            default:
                break;
        }
    }
    strcpy(FileName, "");
    strcat(FileName, Class);
    strcat(FileName, "+");
    strcat(FileName, Section);
    strcat(FileName, "+");
    strcat(FileName, Lab);
    strcat(FileName, "+");
    strcat(FileName, User);
    strcat(FileName, "\0");

    printf("%s\n", Class);
    printf("%s\n", Section);
    printf("%s\n", Lab);
    printf("%s\n", User);
    printf("%s\n", FileName);
    
    int fd = open(FileName, O_CREAT, O_WRONLY);
    
    return (EXIT_SUCCESS);
}
