#include "../header/linked_list_arete.h"
#include "../header/linked_list.h"
#include <stdio.h>
#include <stdlib.h>

//#define DEBUG_LINKED_LIST

#ifdef DEBUG_LINKED_LIST
#include <assert.h>
#endif

static int edge_t_is_equal(void *node_v, void *edge_v)
{
    int node = *((int *) node_v);
    edge_t *edge = (edge_t *) edge_v;
    return !(edge -> node - node);
}

static void edge_t_free(void *edge_v)
{
    edge_t *edge = (edge_t *) edge_v;
    free (edge);
}

static void edge_t_print(void *edge_v)
{
    edge_t *edge = (edge_t *) edge_v;
    printf("node linked : %d\nedge color1 code: %d\nedge color2 code : %d\nedge length : %d\n", edge -> node, edge -> color1, edge -> color2, edge -> length);
}

static edge_t *edge_t_init(int node, int color1, int color2, int length)
{
    edge_t *edge = malloc(sizeof(edge_t));

    if (edge == NULL)
    {
        printf("Allocation failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    edge -> node = node;
    edge -> color1 = color1;
    edge -> color2 = color2;
    edge -> length = length;

    return edge;
}

void edge_list_add(linked_list_t **list, int node, int color1, int color2, int length)
{
    edge_t *edge = edge_t_init(node, color1, color2, length);
    linked_list_t_add(list, edge);
}

edge_t *edge_list_get_node(linked_list_t *list, int node)
{
    if (list == NULL)
    {
        return NULL;
    }

    while (!edge_t_is_equal(&node, list -> head) && list -> tail != NULL)
    {
        list = list -> tail;
    }

    if(edge_t_is_equal(&node, list -> head))
    {
        return (edge_t *) list -> head;
    }else{
        return NULL;
    }
}

void edge_list_rm_node(linked_list_t **list, int node)
{
    linked_list_t_rm(list, &node, edge_t_is_equal, edge_t_free);
}

void edge_list_free(linked_list_t *list)
{
    linked_list_t_free(list, edge_t_free);
}

void edge_list_print(linked_list_t *list)
{
    printf("{\n");

    linked_list_t_print(list, edge_t_print);

    printf("}\n\n");
}

edge_t *edge_list_head(linked_list_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }else{
        return (edge_t *) list -> head;
    }
}

#ifdef DEBUG_LINKED_LIST


//à modifier
int main(void)
{
    /*test edge_t functions*/

    edge_t *edge_test = edge_t_init(5, 6, 7, 8);

    edge_t_print(edge_test);

    free(edge_test);

    /*end edge_t functions test*/

    /*test edge_list_t functions add and free*/

    linked_list_t *edge_list_test0 = NULL;

    for (int i = 0; i < 1024; i++)
    {
        edge_list_add(&edge_list_test0, i, i + 3, i+5, i*2);
    }

    edge_list_free(edge_list_test0);

    edge_list_free(NULL);

    /*end edge_list_t functions test add and free*/

    /*test edge_list_t functions get, rm and print*/
    linked_list_t *edge_list_test1 = NULL;

    for (int i = 0; i < 16; i++)
    {
        edge_list_add(&edge_list_test1, i, i + 3, i+5, i*2);
    }

    assert(edge_list_get_node(edge_list_test1, 10) -> node == 10);

    assert(edge_list_get_node(edge_list_test1, 60) == NULL);

    assert(edge_list_get_node(NULL, 10) == NULL);

    edge_list_print(edge_list_test1);

    edge_list_rm_node(&edge_list_test1, 10);
    
    edge_list_rm_node(&edge_list_test1, 60);

    edge_list_print(edge_list_test1);

    edge_list_rm_node(NULL, 10);

    edge_list_free(edge_list_test1);

    return 0;
}

#endif