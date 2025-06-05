#ifndef PRIORITY_QUEUE_NODE_H
#define PRIORITY_QUEUE_NODE_H

#include "priority_queue.h"

typedef struct double_node_{
    int node;
    int parent;
    int length;
} double_node_t;

/*add an element to the priority queue*/
void node_p_queue_push(p_queue_t **queue, int node, int parent, float priority, int length);

/*remove the head of the queue*/
double_node_t *node_p_queue_pull(p_queue_t **queue);

/*free the queue*/
void node_p_queue_free(p_queue_t *queue);


#endif