#ifndef CALCULATE_PATH_H
#define CALCULATE_PATH_H

#include "../../structures/structures.h"

int *calculate_path(board_t *board, board_t *my_board, union_find_t *abrm, int node_a, int node_b);

#endif