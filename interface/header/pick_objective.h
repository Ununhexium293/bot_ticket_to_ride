#ifndef PICK_OBJECTIVE_H
#define PICK_OBJECTIVE_H

#include "../../structures/structures.h"
#include "../../tickettorideapi/ticketToRide.h"

/*Use the function choose_objective to draw and choose objectives*/
int pick_objective(board_t *board, board_t *my_board, bool *(*choose_objective)(board_t *, board_t *, Objective *));

#endif