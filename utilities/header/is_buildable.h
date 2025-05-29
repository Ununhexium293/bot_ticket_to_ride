#ifndef IS_BULDABLE_H
#define IS_BULDABLE_H

#include "../../structures/structures.h"

/*revois la couleur avec laquelle on prend un chemin, 0 sinon*/
int is_buidable(objective_t *path, board_t *board);

int can_build_something(board_t *board, linked_list_t *list, int forward_view);

#endif