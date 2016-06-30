/***********************************************************
* File Name     : Submission.c
* Purpose       : Submission system for the Grading Environment
* Creation Date : 06-30-2016
* Last Modified : Thu 30 Jun 2016 02:11:46 PM PDT
* Created By    : Mark Shanklin 
***********************************************************/

#include <stdio>
#include <unistd>
#include <stdlib>
#include <ctype>

int main (int argc, int * argv[])
{
    int c;
    c = 0;
    
    char *Class;
    char *Section;
    char *Lab;
    char *User;
    char *FileName;
    
    while(c = getops(argc,argv, "c:C:s:S:l:L:u:U:hH"))
    {
        
        switch(c)
        {
            case c:
                break;
            case C:
                break;
            case s:
                break;
            case S:
                break;
            case l:
                break;
            case L:
                break;
            case u:
                break;
            case U:
                break;
            case h:
                break;
            case H:
                break;
        }
    }
    
    return (EXIT_SUCCESS);
    
}