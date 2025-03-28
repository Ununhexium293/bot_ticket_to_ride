#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct p_queue_{
    void *content;
    void *priority;
    struct p_queue_ *tail;
} p_queue_t;

/*add an element to the priority queue*/
/*  - compare is a function that should return 0 if its fisrt argument is strictly bigger than its second, a non null integr else*/
void p_queue_t_push(p_queue_t **queue, void *content, void *priority, int (*compare)(void *, void *));

/*remove the head of the queue and return its content*/
/*  - free_priority is a function that free the allocated space for priority*/
void *p_queue_t_pull(p_queue_t **queue, void (*free_priority)(void *));

/*free the queue*/
/*  - free_content is a function that free the allocated space for content*/
/*  - free_priority is a function that free the allocated space for priority*/
void p_queue_t_free(p_queue_t *queue, void (*free_content)(void *), void (*free_priority)(void *));

#endif