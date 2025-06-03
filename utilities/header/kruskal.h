#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../../structures/header/graph_board.h"
#include "../../structures/header/union_find.h"

board_t *kruskal(board_t *board, board_t *my_board, float p, float (*priority_calculation)(board_t *board, int node_a, int node_b, float p));

#endif