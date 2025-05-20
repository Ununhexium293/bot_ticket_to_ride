#include "../../structures/structures.h"
#include "../../tickettorideapi/ticketToRide.h"
#include <stdio.h>
#include <stdlib.h>

/*revois la couleur avec laquelle on prend un chemin, 0 sinon*/
static int is_buidable(objective_t *path, board_t *board)
{
    int is_it = 0;
    edge_t *edge = edge_list_get_node(board -> graph[path -> node_1], path -> node_2);

    if (edge -> length < board -> wagons)
    {
        return 0;
    }

    if (edge -> color2 == 0)
    {
        is_it = (board -> cards[edge -> color1 - 1]) - (edge -> length);

        is_it = (is_it >= 0) ? edge -> color1 : 0;
    }else{
        int a = board -> cards[edge -> color1 - 1];
        int b = board -> cards[edge -> color2 - 1];

        is_it = ((a < b) ? b : a) - (edge -> length);

        /*on verrifie que l'on a assez de carte (couleur + loco) pour poser la route*/
        is_it = (is_it + board -> cards[8] >= 0) ? is_it : 0;

        if (is_it == a - (edge -> length))
        {
            is_it = edge -> color1;
        }else if (is_it == b - (edge -> length)){
            is_it = edge -> color2;
        }
    }

    return is_it;
}

static unsigned int nb_loco(int color, board_t *board, int length)
{
    int diff = length - board -> cards[color - 1];

    return (diff >= 0) ? diff : 0;
}

int build_track(board_t *board, board_t *my_board, linked_list_t *path, int forward_view)
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

    linked_list_t *temp = path;
    int ok = 1;

    for (int i = 0; i < forward_view && temp != NULL && ok; i++)
    {
        objective_t *edge = (objective_t *) path -> head;
        int color = is_buidable(edge, board);

        if (color)
        {
            ok = 0;
        }

        if (!ok)
        {
            int length = edge_list_get_node(board -> graph[edge -> node_1], edge -> node_2) -> length;
            unsigned int locos = nb_loco(color, board, length);

            ClaimRouteMove claim;
            claim.from = edge -> node_1;
            claim.to = edge -> node_2;
            claim.color = color;
            claim.nbLocomotives = locos;

            board -> cards[color - 1] -= length - locos;
            board -> cards[8] -= locos;

            board_t_add(my_board, edge -> node_1, edge -> node_2, length , color, 0);
            board_t_rm(board, edge -> node_1, edge -> node_2);

            data -> action = CLAIM_ROUTE;
            data -> claimRoute = claim;
        }
    }

    ResultCode send_move_result = sendMove(data, move);

    if (send_move_result != ALL_GOOD)
    {
        printf("Failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
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

    MoveState state = move -> state;

    free(data);
    free(move);

    return state;
}