#ifndef LISTE_CHAINE_ARRETE_H
#define LISTE_CHAINE_ARRETE_H
#include "linked_list.h"

typedef struct edge_
{
    int node;
    int color1; /*à changer (le type)*/
    int color2;
    int length;
} edge_t;

/*Add an edge to the linked_list_t list by giving the node, the color of the edge and its length*/
void edge_list_add(linked_list_t **list, int node, int color1, int color2, int length);

/*Return the edge connecting to the node given in the list, return NULL if it does not exist*/
edge_t *edge_list_get_node(linked_list_t *list, int node);

/*Return the edge connecting to the node given in the list and remove the node from the list, return NULL if it does not exist*/
void edge_list_rm_node(linked_list_t **list, int node);

/*Free all allocated space from list*/
void edge_list_free(linked_list_t *list);

/*print the edge list*/
void edge_list_print(linked_list_t *list);

/*return the head of the list*/
edge_t *edge_list_head(linked_list_t *list);

#endif