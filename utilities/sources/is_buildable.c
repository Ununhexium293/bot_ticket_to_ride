#include <stdio.h>
#include <stdlib.h>
#include "../utilities.h"

int is_buidable(objective_t *path, board_t *board)
{
    int is_it = 0;
    edge_t *edge = edge_list_get_node(board -> graph[path -> node_1], path -> node_2);

    if (edge -> length > board -> wagons)
    {
        return 0;
    }

    if (edge -> color1 == 9)
    {
        int color = 0;
        int nb = board -> cards[color];
        for (int i = 1; i < 8; i++)
        {
            if (board -> cards[i] > nb)
            {
                nb = board -> cards[i];
                color = i;
            }
        }
        color += 1;

        if (nb + board -> cards[8] >= edge -> length)
        {
            is_it = color;
        }
        
    }else if (edge -> color2 == 0)
    {
        is_it = (board -> cards[edge -> color1 - 1]) - (edge -> length);

        is_it = (is_it + board -> cards[8] >= 0) ? edge -> color1 : 0;
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

static int color_needed(edge_t *edge, board_t *board)
{
    int is_it;

    if (edge -> color1 == 9)
    {
        int color = 0;
        int nb = board -> cards[color];
        for (int i = 1; i < 8; i++)
        {
            if (board -> cards[i] > nb)
            {
                nb = board -> cards[i];
                color = i;
            }
        }
        color += 1;

        is_it = color;
        
    }else if (edge -> color2 == 0)
    {
        is_it = (board -> cards[edge -> color1 - 1]) - (edge -> length);

        is_it = edge -> color1;
    }else{
        int a = board -> cards[edge -> color1 - 1];
        int b = board -> cards[edge -> color2 - 1];

        is_it = ((a < b) ? edge -> color2 : edge -> color1);
    }

    return is_it;
}

int can_build_something(board_t *board, linked_list_t *list, int forward_view)
{
    int ok = -1;

    int colors[9];

    for (int i = 0; i < 9; i++)
    {
        colors[i] = board -> cards[i];
    }

    for (int i = 0; i < forward_view && ok == -1 && list != NULL; i++)
    {
        objective_t *path = (objective_t *) list -> head;
        edge_t *edge = edge_list_get_node(board -> graph[path -> node_1], path -> node_2);

        if (is_buidable(path, board))
        {
            ok = i;
        }

        int color = color_needed(edge, board);

        board -> cards[color] -= edge -> length;

        list = list -> tail;
    }

    for (int i = 0; i < 9; i++)
    {
        board -> cards[i] = colors[i];
    }

    return ok;
}