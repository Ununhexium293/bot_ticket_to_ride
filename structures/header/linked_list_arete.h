#ifndef LISTE_CHAINE_ARRETE_H
#define LISTE_CHAINE_ARRETE_H

typedef struct edge_{
    int node;
    int color; /*à changer (le type)*/
    int length;
} edge_t;

edge_t *edge_t_init(int node, int color, int length);



typedef struct edge_list_{
    edge_t *edge;
    struct edge_list_ *next;
} edge_list_t;

edge_list_t *edge_list_t_add(edge_list_t *list, int node, int color, int length);

edge_t *edge_list_t_get_node_n(edge_list_t *list, int node);

edge_t *edge_list_t_rm_node_n(edge_list_t *list, int node);

edge_t *edge_list_t_free(edge_list_t *list);

#endif