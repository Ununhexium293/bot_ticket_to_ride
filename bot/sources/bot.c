#include <stdlib.h>
#include "../../tickettorideapi/ticketToRide.h"
#include "../../tickettorideapi/clientAPI.h"
#include "../../interface/interface.h"
#include "../../structures/structures.h"
#include "../../utilities/utilities.h"
#include "../header/my_turn.h"

extern int DEBUG_LEVEL;
#define DEBUG_CONNECT
#define DEBUG_HOME

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

void bot(char *setting)
{
    float p = 0.5;
    float overlap_choice = 0.1;
    int forward_view = 3;
    #ifdef DEBUG_CONNECT
    DEBUG_LEVEL=INTERN_DEBUG;
    #endif

    int restart = 0;

    GameData *data = connect_bot("bot_quentin_lv___", setting);

    do
    {
        if (restart)
        {
            sendGameSettings(setting, data);
        }
        restart = 1;

        board_t *board = data_to_board(data);
        int tab[4] = {1, 2, 3, 4};

        board_t *my_board = board_t_init(board -> nb_node, tab);

        int turn = data -> starter;

        int first = 1;

        printBoard();

        int state = NORMAL_MOVE;

        while (state == NORMAL_MOVE)
        {
            if (!turn)
            {
                my_turn(board, my_board, p, overlap_choice, forward_view, first);
                first = 0;
            }else{
                opponent_turn(board);
            }
            turn = 1 - turn;
        }

        board_t_free(board);
        board_t_free(my_board);
    }while(1);
}