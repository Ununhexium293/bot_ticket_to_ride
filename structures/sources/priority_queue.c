#include <stdlib.h>
#include <stdio.h>
#include "../header/priority_queue.h"

void p_queue_t_push(p_queue_t **queue, void *content, void *priority, int (*compare)(void *, void *))
{
    if (queue == NULL)
    {
        return;
    }

    p_queue_t *new_element = malloc(sizeof(p_queue_t));

    if (new_element == NULL)
    {
        printf("Allocation failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    new_element -> content = content;
    new_element -> priority = priority;

    p_queue_t *previous = NULL;
    p_queue_t *current = *queue;

    while (current != NULL && compare(priority, current -> priority))
    {
        previous = current;
        current = current -> tail;
    }

    new_element -> tail = current;

    if (previous == NULL)
    {
        *queue = new_element;
    }else{
        previous -> tail = new_element;
    }
}

void *p_queue_t_pull(p_queue_t **queue, void (*free_priority)(void *))
{
    if (queue == NULL)
    {
        return NULL;
    }

    p_queue_t *temp = *queue;
    *queue = (*queue) -> tail;

    void *content = temp -> content;
    if (free_priority != NULL)
    {
        free_priority(temp -> priority);
    }
    free(temp);

    return content;
}

void p_queue_t_free(p_queue_t *queue, void (*free_content)(void *), void (*free_priority)(void *))
{
    while (queue != NULL)
    {
        void *content = p_queue_t_pull(&queue, free_priority);
        if (free_content != NULL)
        {
            free_content(content);
        }
    }
}