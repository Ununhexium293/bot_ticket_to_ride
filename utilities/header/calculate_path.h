#ifndef CALCULATE_PATH_H
#define CALCULATE_PATH_H

#include "../../structures/structures.h"

int *calculate_path(board_t *board, board_t *my_board, union_find_t *abrm, int node_a, int node_b);

linked_list_t *path_planning(board_t *board, board_t *my_board, float p, float (*priority_calculation)(board_t *, int, int, float));

#endif