#ifndef GRAPH_BOARD_H
#define GRAPH_BOARD_H

#include "linked_list.h"
#include "linked_list_arete.h"
#include "linked_list_objective.h"

typedef struct board_
{
    linked_list_t **graph;
    int nb_node;
    int *cards;
    int wagons;
    int opponent_wagon;
    linked_list_t *objectives;
} board_t;

/**Create an empty board */
board_t *board_t_init(int nb_node, int cards[4]);

/*Add an edge to the graph, linking node_a and noe_b*/
void board_t_add(board_t *board, int node_a, int node_b, int length, int color1, int color2);

/*Remove an edge between node_a and node_b from the graph*/
void board_t_rm(board_t *board, int node_a, int node_b);

/*Free all allocated space from the board*/
void board_t_free(board_t *board);

#endif