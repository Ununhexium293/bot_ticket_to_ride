#ifndef CALCULATE_PATH_H
#define CALCULATE_PATH_H

#include "../../structures/structures.h"

/*need to free output*/
int *calculate_path(board_t *board, board_t *my_board, board_t *abrm, int node_a, int node_b);

/*need to free output*/
linked_list_t *path_planning(board_t *board, board_t *my_board, float p, int forward_view, float (*priority_calculation)(board_t *, int, int, float));

#endif