#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct p_queue_{
    int node;
    float priority;
    struct p_queue_ *tail;
} p_queue_t;

/*add an element to the priority queue*/
void p_queue_t_add(p_queue_t **queue, int node, float priority);

/*remove the head of the queue*/
void p_queue_t_rm(p_queue_t **queue);

/*free the queue*/
void p_queue_t_free(p_queue_t *queue);


#endif