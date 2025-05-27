#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../../structures/header/graph_board.h"

int *dijkstra(board_t *board, board_t *my_board, int node_a, int node_b, float proportion, float (*priority_calculation)(board_t *board, int node_a, int node_b, float p));

#endif