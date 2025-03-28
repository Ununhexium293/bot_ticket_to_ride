#include <stdlib.h>
#include <stdio.h>
#include "../header/priority_queue_node.h"

//#define DEBUG_PRIORITY_QUEUE

void node_p_queue_t_add(p_queue_t **queue, int node, int parent, float priority)
{
    p_queue_t *temp_prec = NULL;
    p_queue_t *temp = *queue;

    while (temp != NULL && temp -> priority < priority)
    {
        temp_prec = temp;
        temp = temp -> tail;
    }

    p_queue_t *new_head = malloc(sizeof(p_queue_t));
    new_head -> node = node;
    new_head -> parent = parent;
    new_head -> priority = priority;
    new_head -> tail = temp;

    if (temp_prec == NULL)
    {
        *queue = new_head;
    }else{
        temp_prec -> tail = new_head;
    }
}

void node_p_queue_t_rm(p_queue_t **queue)
{
    if (queue != NULL && *queue != NULL)
    {
        p_queue_t *temp = *queue;
        *queue = (*queue) -> tail;
        free(temp);
    }
}

void node_p_queue_t_free(p_queue_t *queue)
{
    while (queue != NULL)
    {
        p_queue_t_rm(&queue);
    }
}

#ifdef DEBUG_PRIORITY_QUEUE

int main(void)
{
    /*test priority queue*/

    p_queue_t *test = NULL;

    p_queue_t_add(&test, 1, 5.);
    p_queue_t_add(&test, 2, 2.);
    p_queue_t_add(&test, 3, 4.);
    p_queue_t_add(&test, 4, 7.);
    p_queue_t_add(&test, 5, 4.5);

    for (int i = 0; i < 5; i++)
    {
        printf("node : %d - priority : %.3f\n", test -> node, test -> priority);
        p_queue_t_rm(&test);
    }

    p_queue_t_free(test);

    /*end test priority queue*/
}

#endif