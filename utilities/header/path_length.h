#ifndef PATH_LENGTH_H 
#define PATH_LENGTH_H

#include "../../structures/structures.h"

int path_length(board_t *board, int *path, int node_a, int node_b);

int *path_overlap_length(board_t *board, int **path, int *node_a, int *node_b);

#endif