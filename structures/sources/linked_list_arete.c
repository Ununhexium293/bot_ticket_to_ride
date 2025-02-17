#include "../header/linked_list_arete.h"

//#define DEBUG

edge_t *edge_t_init(int node, int color, int length)
{
    edge_t *edge = malloc(sizeof(edge_t));

    if (edge == NULL)
    {
        printf("Allocation of size edge_t failed.\n");
        exit(EXIT_FAILURE);
    }

    edge -> node = node;
    edge -> color = color;
    edge -> length = length;

    return edge;
}

edge_list_t *edge_list_t_add(edge_list_t *list, int node, int color, int length)
{
    edge_t *edge = edge_t_init(node, color, length);

    edge_list_t *edge_list = malloc(sizeof(edge_list_t));

    if (edge_list == NULL)
    {
        printf("Allocation of size edge_list_t failed.\n");
        exit(EXIT_FAILURE);
    }

    edge_list -> edge = edge;
    edge_list -> next = list;

    return edge_list;
}