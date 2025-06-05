#include <stdio.h>
#include <stdlib.h>
#include "../../tickettorideapi/ticketToRide.h"
#include "../../tickettorideapi/clientAPI.h"
#include "../../interface/interface.h"
#include "../../structures/structures.h"
#include "../../utilities/utilities.h"
#include "../header/my_turn.h"

static board_t *data_to_board(GameData *data)
{
    board_t *board = board_t_init(data -> nbCities, (int *) data -> cards);

    for (int i = 0; i < data -> nbTracks; i++)
    {
        int j = i * 5;
        board_t_add(board, data -> trackData[j], data -> trackData[j + 1], data -> trackData[j + 2], data -> trackData[j + 3], data -> trackData[j + 4]);
    }

    return board;
}

void bot(char *setting, char *name, int p, int overlap_choice, int forward_view_place, int forward_view_pick)
{
    #ifdef DEBUG_CONNECT
    DEBUG_LEVEL= NONE; //INTERN_DEBUG;
    #endif

    int nb_won = 0;
    int total = 0;

    int restart = 0;

    GameData *data = connect_bot(name, setting);

    do
    {
        if (restart)
        {
            sendGameSettings(setting, data);
        }
        restart = 1;

        printf("\n seed : %d\n\n", data -> gameSeed);
        fflush(stdout);

        board_t *board = data_to_board(data);
        int tab[4] = {1, 2, 3, 4};

        board_t *my_board = board_t_init(board -> nb_node, tab);

        int turn = data -> starter;

        int first = 1;

        int state = NORMAL_MOVE;

        while (state == NORMAL_MOVE)
        {
            
            if (!turn)
            {
                state = my_turn(board, my_board, p, overlap_choice, forward_view_place, forward_view_pick, first);
                first = 0;
            }else{
                state = opponent_turn(board);
            }
            turn = 1 - turn;
        }

        total ++;
        
        if ((state == 1 && turn == 0)||(state == -1 && turn == 1))
        {
            printf("loose %d\n", total - nb_won);
        }else{
            nb_won ++;
            printf("won %d\n", nb_won);
        }

        printf("total %d\n", total);

        board_t_free(board);
        board_t_free(my_board);
    }while(total < 100);
    
    disconnect_bot(data);
}