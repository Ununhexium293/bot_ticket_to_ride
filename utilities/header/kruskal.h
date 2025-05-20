#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../../structures/header/graph_board.h"

int *kruskal(board_t *board, float p, int (*priority_calculation)(board_t *board, int node_a, int node_b, float p));

#endif