#include <stdlib.h>
#include <stdio.h>
#include "../header/priority_queue_node.h"

//#define DEBUG_PRIORITY_QUEUE

static int float_compare(void *a, void *b)
{
    return (*((float *) a) < *((float *) b)) ? 0 : 1;
}

void node_p_queue_push(p_queue_t **queue, int node, int parent, float priority, int length)
{
    if (queue == NULL)
    {
        return;
    }

    double_node_t *nodes = malloc(sizeof(double_node_t));

    if (nodes == NULL)
    {
        printf("Allocation failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    float *prio = malloc(sizeof(float));

    if (prio == NULL)
    {
        printf("Allocation failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    *prio = priority;

    nodes -> node = node;
    nodes -> parent = parent;
    nodes -> length = length;

    p_queue_t_push(queue, nodes, prio, float_compare);
}

double_node_t *node_p_queue_pull(p_queue_t **queue)
{
    return (double_node_t *) p_queue_t_pull(queue, free);
}

void node_p_queue_free(p_queue_t *queue)
{
    p_queue_t_free(queue, free, free);
}

#ifdef DEBUG_PRIORITY_QUEUE

int main(void)
{
    /*test priority queue*/

    p_queue_t *test = NULL;

    node_p_queue_push(&test, 1, 2, 5.);
    node_p_queue_push(&test, 2, 3, 2.);
    node_p_queue_push(&test, 3, 4, 4.);
    node_p_queue_push(&test, 4, 5, 7.);
    node_p_queue_push(&test, 5, 1, 4.5);

    for (int i = 0; i < 5; i++)
    {
        float prio = *((float *) (test -> priority));
        double_node_t *nodes = node_p_queue_pull(&test);
        printf("node : %d - priority : %.3f\n", nodes -> node, prio);
        fflush(stdout);
        free(nodes);
    }

    node_p_queue_free(test);

    /*end test priority queue*/
}

#endif