#ifndef LISTE_CHAINE_ARRETE_H
#define LISTE_CHAINE_ARRETE_H

typedef struct edge_
{
    int node;
    int color; /*à changer (le type)*/
    int length;
} edge_t;

/*print the edge*/
void edge_t_print(edge_t *edge);

typedef struct edge_list_
{
    edge_t *edge;
    struct edge_list_ *next;
} edge_list_t;

/*Add an edge to the edge_list_t list by giving the node, the color of the edge and its length*/
void edge_list_t_add(edge_list_t **list, int node, int color, int length);

/*Return the edge connecting to the node given in the list, return NULL if it does not exist*/
edge_t *edge_list_t_get_node(edge_list_t *list, int node);

/*Return the edge connecting to the node given in the list and remove the node from the list, return NULL if it does not exist*/
void edge_list_t_rm_node(edge_list_t **list, int node);

/*Free all allocated space from list*/
void edge_list_t_free(edge_list_t *list);

/*print the edge list*/
void edge_list_t_print(edge_list_t *list);

#endif