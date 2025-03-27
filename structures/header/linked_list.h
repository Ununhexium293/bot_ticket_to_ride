#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct linked_list_
{
    void *head;
    struct linked_list_ *tail;
}linked_list_t;

/*add the head to the list*/
void linked_list_t_add(linked_list_t **list, void *head);

/*remove one element from the list and free its allocated space*/
/*does nothing if head isn't in the list*/
/*  - is_equal is a function that return a non null integer if both its argument are equal, 0 else*/
/*  - free_head is a function that free the allocated space of the head*/
void linked_list_t_rm(linked_list_t **list, void *head, int (*is_equal)(void *, void *), void (*free_head)(void *));

/*free the allocated space of list*/
/*  - free_head is a function that free the allocated space of the head*/
void linked_list_t_free(linked_list_t *list, void (*free_head)(void *));

/*print the element of the list*/
/*  - print_head is a function that print the wanted information from head*/
void linked_list_t_print(linked_list_t *list, void (*print_head)(void *));

#endif