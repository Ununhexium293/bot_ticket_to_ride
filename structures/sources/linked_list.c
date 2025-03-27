#include <stdlib.h>
#include <stdio.h>
#include "../header/linked_list.h"

#include <assert.h>

void linked_list_t_add(linked_list_t **list, void *head)
{
    /*protect against dereferencing a NULL pointer*/
    if (list == NULL)
    {
        return;
    }

    linked_list_t *new_element = malloc(sizeof(linked_list_t));
    
    if (new_element == NULL)
    {
        printf("Allocation failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
     
    new_element -> head = head;
    new_element -> tail = *list;
     
    *list = new_element;
}

void linked_list_t_rm(linked_list_t **list, void *head, int (*is_equal)(void *, void *), void (*free_head)(void *))
{
    /*protect against dereferencing a NULL pointer*/
    if (list == NULL)
    {
        return;
    }

    linked_list_t *previous = NULL;
    linked_list_t *current = *list;

    /*Browse through the list intil either we got to the end of the list or we find the head that we seek*/
    while (current != NULL && !is_equal(head, current -> head))
    {
        previous = current;
        current = current -> tail;
    }

    /*if current is NULL that mean that we got to the end of the list without finding head*/
    if (current != NULL)
    {
        if (previous == NULL)
        {
            *list = current -> tail;
        }else{
            previous -> tail = current -> tail;
        }

        free_head(current -> head);
        free(current);
    }
}

void linked_list_t_free(linked_list_t *list, void (*free_head)(void *))
{
    while (list != NULL)
    {
        linked_list_t *temp = list;
        list = list -> tail;

        free_head(temp -> head);
        free(temp);
    }
}

void linked_list_t_print(linked_list_t *list, void (*print_head)(void *))
{
    while (list != NULL)
    {
        print_head(list -> head);

        list = list -> tail;
    }
}