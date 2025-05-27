#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../../structures/header/graph_board.h"
#include "../../structures/header/union_find.h"

union_find_t *kruskal(board_t *board, float p, float (*priority_calculation)(board_t *board, int node_a, int node_b, float p));

#endif