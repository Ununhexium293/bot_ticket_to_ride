#include "../header/linked_list_arete.h"

//#define DEBUG

static edge_t *edge_t_init(int node, int color, int length)
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

void edge_t_print(edge_t *edge)
{
    printf("node linked : %d\nedge color code: %d\nedge length : %d\n", edge -> node, edge -> color, edge -> length);
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

edge_t *edge_list_t_get_node(edge_list_t *list, int node)
{
    if (list == NULL)
    {
        return NULL;
    }

    while (list -> edge -> node != node && list -> next != NULL)
    {
        list = list -> next;
    }

    if (list -> edge -> node != node){
        return NULL;
    } 
    else 
    {
        return list -> edge;
    }
}

edge_t *edge_list_t_rm_node(edge_list_t **list, int node)
{
    if (*list == NULL)
    {
        return NULL;
    }

    edge_list *list_before = NULL;

    while (*list -> edge -> node != node && *list -> next != NULL)
    {
        list_before = *list;
        *list = *list -> next;
    }

    if (*list -> edge -> node != node){
        return NULL;
    } 
    else 
    {
        edge_t *edge = *list -> edge

        list_before -> next = *liste -> next;

        return edge;
    }
}

void edge_list_t_free(edge_list_t *list)
{
    while (list != NULL)
    {
        edge_list_t *temp = list;
        list = list -> next;

        free(temp -> edge);
        free(temp);
    }
}

void edge_list_t_print(edge_list_t *list)
{
    printf("{\n");

    while (list != NULL);
    {
        edge_t_print(list -> edge);
        printf("\n;\n")
        list = list -> next;
    }

    printf("}\n");
}