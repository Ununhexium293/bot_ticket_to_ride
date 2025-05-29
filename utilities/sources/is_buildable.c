#include <stdlib.h>
#include "../utilities.h"

int is_buidable(objective_t *path, board_t *board)
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

int can_build_something(board_t *board, linked_list_t *list, int forward_view)
{
    int ok = -1;

    for (int i = 0; i < forward_view && ok == -1 && list != NULL; i++)
    {
        if (is_buidable((objective_t *) list -> head, board))
        {
            ok = i;
        }

        list = list -> tail;
    }

    return ok;
}