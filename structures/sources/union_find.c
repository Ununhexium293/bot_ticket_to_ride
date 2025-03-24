#include <stdlib.h>
#include <stdio.h>
#include "../header/union_find.h"

int union_find_t_find(union_find_t *arm, int node)
{
    int current = arm -> former[node];
    while (current != arm -> former[current])
    {
        current = arm -> former[current];
    }
    return current;
}