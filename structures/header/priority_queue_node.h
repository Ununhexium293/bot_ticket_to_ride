#ifndef PRIORITY_QUEUE_NODE_H
#define PRIORITY_QUEUE_NODE_H

typedef struct p_queue_{
    int node;
    int parent;
    float priority;
    struct p_queue_ *tail;
} p_queue_t;

/*add an element to the priority queue*/
void node_p_queue_t_add(p_queue_t **queue, int node, int parent, float priority);

/*remove the head of the queue*/
void node_p_queue_t_rm(p_queue_t **queue);

/*free the queue*/
void node_p_queue_t_free(p_queue_t *queue);


#endif