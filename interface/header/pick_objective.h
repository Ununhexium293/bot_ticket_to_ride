#ifndef PICK_OBJECTIVE_H
#define PICK_OBJECTIVE_H

#include "../../structures/structures.h"
#include "../../tickettorideapi/ticketToRide.h"

/*Use the function choose_objective to draw and choose objectives*/
int pick_objective(board_t *board, board_t *my_board, float p, float overlap_choice, float (*priority_calculation_)(board_t *, int, int, float), bool *(*choose_objective)(board_t *, board_t *, Objective *, float, float , float (*priority_calculation)(board_t *, int, int, float)));

#endif