#include "../header/linked_list_arete.h"
#include <stdio.h>
#include <stdlib.h>

#define DEBUG_LINKED_LIST

#ifdef DEBUG_LINKED_LIST
#include <assert.h>
#endif

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

void edge_list_t_add(edge_list_t **list, int node, int color, int length)
{
    edge_t *edge = edge_t_init(node, color, length);

    edge_list_t *edge_list = malloc(sizeof(edge_list_t));

    if (edge_list == NULL)
    {
        printf("Allocation of size edge_list_t failed.\n");
        exit(EXIT_FAILURE);
    }

    edge_list -> edge = edge;
    edge_list -> next = *list;
    *list = edge_list;
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

void edge_list_t_rm_node(edge_list_t **list, int node)
{
    if (list != NULL && *list != NULL)
    {
        edge_list_t *temp = *list;

        edge_list_t *list_before = NULL;

        while (temp -> edge -> node != node && temp -> next != NULL)
        {
            list_before = temp;
            temp = temp -> next;
        }

        if (temp -> edge -> node == node){
            list_before -> next = temp -> next;

            free(temp -> edge);
            free(temp);
        }
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

    while (list != NULL)
    {
        edge_t_print(list -> edge);
        printf("\n;\n\n");
        list = list -> next;
    }

    printf("}\n\n");
}

#ifdef DEBUG_LINKED_LIST

int main(int argc, char **argv)
{
    /*test edge_t functions*/

    edge_t *edge_test = edge_t_init(5, 6, 8);

    edge_t_print(edge_test);

    free(edge_test);

    /*end edge_t functions test*/

    /*test edge_list_t functions add and free*/

    edge_list_t *edge_list_test0 = NULL;

    for (int i = 0; i < 1024; i++)
    {
        edge_list_t_add(&edge_list_test0, i, i+5, i*2);
    }

    edge_list_t_free(edge_list_test0);

    edge_list_t_free(NULL);

    /*end edge_list_t functions test add and free*/

    /*test edge_list_t functions get, rm and print*/
    edge_list_t *edge_list_test1 = NULL;

    for (int i = 0; i < 16; i++)
    {
        edge_list_t_add(&edge_list_test1, i, i+5, i*2);
    }

    assert(edge_list_t_get_node(edge_list_test1, 10) -> node == 10);

    assert(edge_list_t_get_node(edge_list_test1, 60) == NULL);

    assert(edge_list_t_get_node(NULL, 10) == NULL);



    edge_list_t_print(edge_list_test1);

    edge_list_t_rm_node(&edge_list_test1, 10);

    edge_list_t_rm_node(&edge_list_test1, 60);

    edge_list_t_print(edge_list_test1);



    edge_list_t_rm_node(NULL, 10);

    edge_list_t_free(edge_list_test1);

    return 0;
}

#endif