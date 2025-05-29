#include <stdio.h>
#include <stdlib.h>
#include "../header/pick_card.h"

static int send_move_pick_card(int choosen_card, MoveData *data, MoveResult *move, board_t *board)
{
    if (choosen_card == 0)
    {
        data -> action = DRAW_BLIND_CARD;
    }else
    {
        data -> action = DRAW_CARD;
        data -> drawCard = choosen_card;
        board -> cards[choosen_card - 1] += 1;
    }

    ResultCode send_move_result = sendMove(data, move);

    if (send_move_result != ALL_GOOD || move -> state != NORMAL_MOVE)
    {
        return move -> state;
    }

    if (choosen_card == 0)
    {
        board -> cards[move -> card - 1] += 1;
    }

    if (move -> opponentMessage != NULL)
    {
        printf("opponent message :\n");
        printf(move -> opponentMessage);
        printf("\n");
        free(move -> opponentMessage);
    }

    if (move -> message != NULL)
    {
        printf("opponent message :\n");
        printf(move -> message);
        printf("\n");
        free(move -> message);
    }

    return move -> state;
}

int pick_card(board_t *board, linked_list_t *path, int forward_wiew, int (*to_pick)(board_t *, linked_list_t *, int, int))
{
    MoveData *data = malloc(sizeof(MoveData));
    if (data == NULL)
    {
        printf("Allocation failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    MoveResult *move = malloc(sizeof(MoveResult));
    if (move == NULL)
    {
        printf("Allocation failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    /*_____________________________*/

    int choosen_card = to_pick(board, path, forward_wiew, 1);

    send_move_pick_card(choosen_card, data, move, board);

    /*_____________________________*/

    
    if (choosen_card != 9)
    {
        choosen_card = to_pick(board, path, forward_wiew, 0);

        send_move_pick_card(choosen_card, data, move, board);
    }

    MoveState state = move -> state;

    free(data);
    free(move);

    return state;
}