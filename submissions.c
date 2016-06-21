/***********************************************************
* File Name     : submissions.c
* Purpose       : A program used to handle submission to the grading environment
* Creation Date : 06-21-2016
* Last Modified : Tue 21 Jun 2016 11:10:02 AM PDT
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
    
    while(c = getops(argc,argv, "c:C:s:S:l:L:hH"))
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
            case h:
                break;
            case H:
                break;
        }
    }
    return (EXIT_SUCCESS);
}
