#include <stdlib.h>
#include <stdio.h>
#include "../header/union_find.h"

union_find_t *union_find_t_init(int nb_node)
{
    union_find_t *arm = malloc(sizeof(union_find_t));

    if (arm == NULL)
    {
        printf("Allocation of size union_find_t failed.\n");
        exit(EXIT_FAILURE);
    }

    int *former = malloc(sizeof(int) * nb_node);
    if (former == NULL)
    {
        printf("Allocation of size int * nb_node failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nb_node; i++)
    {
        former[i] = i;
    }

    int *rank = malloc(sizeof(int) * nb_node);
    if (rank == NULL)
    {
        printf("Allocation of size int * nb_node failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nb_node; i++)
    {
        rank[i] = 0;
    }

    arm -> former = former;
    arm -> nb_node = nb_node;
    arm -> rank = rank;

    return arm;
}

int union_find_t_find(union_find_t *arm, int node)
{
    int current = arm -> former[node];
    while (current != arm -> former[current])
    {
        current = arm -> former[current];
    }
    return current;
}

void union_find_t_union(union_find_t *arm, int node_a, int node_b)
{
    int rep_a = union_find_t_find(arm, node_a);
    int rep_b = union_find_t_find(arm, node_b);

    if (arm -> rank[rep_a] > arm -> rank[rep_b])
    {
        arm -> former[rep_b] = rep_a;
    }else{
        arm -> former[rep_a] = rep_b;

        if (arm -> rank[rep_a] = arm -> rank[rep_b])
        {
            arm -> rank[rep_b] += 1;
        }
    }
}

void union_find_t_free(union_find_t *arm)
{
    free(arm -> former);
    free(arm -> rank);
    free(arm);
}