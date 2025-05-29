#ifndef CHOOSE_OBJ_H
#define CHOOSE_OBJ_H

#include "../../structures/structures.h"
#include "../../tickettorideapi/ticketToRide.h"

bool *choose_objective(board_t *board, board_t *my_board, Objective *objs, float p, float overlap_choice, float (*priority_calculation)(board_t *, int, int, float));

bool *choose_objective_start(board_t *board, board_t *my_board, Objective *objs, float p, float overlap_choice, float (*priority_calculation)(board_t *, int, int, float));

#endif