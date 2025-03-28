#include <stdlib.h>
#include <stdio.h>

int point(int length)
{
    switch(length)
    {
        case 1 : return 1;
        case 2 : return 2;
        case 3 : return 4;
        case 4 : return 7;
        case 5 : return 10;
        case 6 : return 15;
        default : 
            printf("Chemin trop long : %d\n", length);
            exit(EXIT_FAILURE);
    }
}