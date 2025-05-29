#ifndef PICK_CARD_H
#define PICK_CARD_H

#include "../../structures/structures.h"
#include "../../tickettorideapi/ticketToRide.h"

int pick_card(board_t *board, linked_list_t *path, int forward_view, int (*to_pick)(board_t *, linked_list_t *, int, int));

#endif