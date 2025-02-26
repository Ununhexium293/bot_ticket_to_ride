#ifndef GRAPH_BOARD_H
#define GRAPH_BOARD_H

#include "linked_list_arete.h"

typedef struct board_
{
    edge_list_t *graph;
    int nb_node;
} board_t;

/*Create an empty board*/
board_t *board_t_init(int nb_node);

/*Add an edge to the graph, linking node_a and noe_b*/
void board_t_add(board_t *board, int node_a, int node_b);

/*Remove an edge between node_a and node_b from the graph*/
void board_t_rm(board_t *board, int node_a, int node_b, int color);

/*Free all allocated space from the board*/
void board_t_free(board_t *board);

#endif