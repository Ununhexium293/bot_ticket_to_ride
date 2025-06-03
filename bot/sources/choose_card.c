#include <stdlib.h>
#include "../../structures/structures.h"
#include "../../tickettorideapi/ticketToRide.h"

int choose_card(board_t *board, linked_list_t *path, int forward_wiew, int loco)/*il faut gerer les chemin multicolore*/
{
    int choice = 0;

    int cards[10];

    for (int i = 1; i <= 9; i++)
    {
        cards[i] = board -> cards[i];
    }
    cards[0] = ~0;

    BoardState *face_up = malloc(sizeof(BoardState));
    
    getBoardState(face_up);

    for (int i = 0; i < forward_wiew && path != NULL && !choice; i++)
    {
        objective_t *track = (objective_t *) path -> head;

        edge_t *edge = edge_list_get_node(board -> graph[track -> node_1], track -> node_2);

        int color = ((cards[edge -> color1] > cards[edge -> color2]) ? edge -> color1 : edge -> color2);

        if (color == 9)
        {
            int max = 0;

            for (int i = 0; i < 8; i++)
            {
                if (max < board -> cards[i])
                {
                    max = board  -> cards[i];
                    color = i;
                }
            }
        }

        for (int j = 0; j < 5 && !choice; j++)
        {
            if (face_up -> card[j] == color)
            {
                choice = face_up -> card[j];
            }
        }

        if (!choice)
        {
            if (loco && edge -> length - cards[color] - cards[9] == 1)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (face_up -> card[j] == 9)
                    {
                        choice = 9;
                    }
                }
            }else{
                cards[color] -= edge -> length;
            }
        }

        path = path -> tail;
    }

    free(face_up);
    
    return choice;

}