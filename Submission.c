/***********************************************************
* File Name     : Submission.c
* Purpose       : Submission system for the Grading Environment
* Creation Date : 06-30-2016
* Last Modified : Thu 30 Jun 2016 02:11:46 PM PDT
* Created By    : Mark Shanklin 
***********************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, int * argv[])
{
    int command = 0;
    int fileCount = 0;
    int i = 0;
    
    char *Class;
    char *Section;
    char *Lab;
    char *User;
    char **FileName;
    
    FileName = NULL;
    
    while((command = getops(argc,argv, "c:C:s:S:l:L:u:U:hH")) != -1)
    {
        
        switch(command)
        {
            case 'c':
            case 'C':
                optind--;
                for (i = optind; i < argc && (*argv[i] != '-'); i++)
                {
                    if (strlen(basename(argv[i])) < MAX_FILE_NAME_LEN)
                    {
                        Class = strdup(argv[i]);
                    }
                }
                break;
            case 's':
            case 'S':
                
                break;
            case 'l':
            case 'L':
                
                break;
            case 'u':
            case 'U':
                
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
    
    printf("%s\n", Class);
    
    
    for (i = 0; i < fileCount; i++)
    {
        fprintf(stdout, "%s\n", FileName[i]);
    }
    
    return (EXIT_SUCCESS);
    
}