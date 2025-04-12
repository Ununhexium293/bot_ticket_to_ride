#ifndef LINKED_LIST_OBJECTIVE_H
#define LINKED_LIST_OBJECTIVE_H

#include "linked_list.h"

typedef struct {
    int node_1;
    int node_2;
    int point;
} objective_t;

void objective_list_add(linked_list_t **list, int node_1, int node_2, int point);

void objective_list_rm(linked_list_t **list, int node_1, int node_2);

void objective_list_free(linked_list_t *list);

void objective_list_print(linked_list_t *list);
#endif