#include <stdio.h>
#include <stdlib.h>
#include "../../structures/structures.h"
#include "../../tickettorideapi/ticketToRide.h"

int opponent_turn(board_t *board)
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

    ResultCode result = getMove(data, move);
    if (result != ALL_GOOD)
    {
        return EXIT_FAILURE;
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

    int replay = 0;

    if (data -> action == CLAIM_ROUTE)
    {
        int length = edge_list_get_node(board -> graph[data -> claimRoute.from], data -> claimRoute.to) -> length;

        board_t_rm(board, data -> claimRoute.from, data -> claimRoute.to);

        board -> opponent_wagon -= length;
    }else if (data -> action == DRAW_BLIND_CARD)
    {
        result = getMove(data, move);
        replay = 1;
    }else if (data -> action == DRAW_CARD)
    {
        if (data -> drawCard != LOCOMOTIVE || move -> replay)
        {
            result = getMove(data, move);
            replay = 1;
        }
    }else{
        result = getMove(data, move);
        replay = 1;
    }

    if (replay)
    {
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
    }

    MoveState state = move -> state;

    free(data);
    free(move);

    return state;
}