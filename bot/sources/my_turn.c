#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../interface/interface.h"
#include "../../structures/structures.h"
#include "../../utilities/utilities.h"
#include "../../tickettorideapi/ticketToRide.h"
#include "../header/choose_obj.h"
#include "../header/choose_card.h"

/*important :
    modif dijsktra pour prendre en compte le nombre de wagon
*/

//#define PRINT_DO

static void update_obj(board_t *board, board_t *my_board)
{
    linked_list_t *objs = board -> objectives;

    int *cards = malloc(sizeof(int) * 4);
    for (int i = 0; i < 4; i++)
    {
        cards[i] = 5;
    }
    board_t *empty = board_t_init(board -> nb_node, cards);
    free(cards);

    while (objs != NULL)
    {
        objective_t *obj = ((objective_t *) objs -> head);
        
        int *path = dijkstra(empty, my_board, obj -> node_1, obj -> node_2, 0.5, priority_calculation);

        if (path == NULL)
        {
            ;
        }else {
            objective_list_rm(&(board -> objectives), obj -> node_1, obj -> node_2);
            free(path);
        }

        /*+ pour chemin impossible*/
        path = dijkstra(board, my_board, obj -> node_1, obj -> node_2, 0.5, priority_calculation);
        if (path != NULL)
        {
            ;
        }else {
            objective_list_rm(&(board -> objectives), obj -> node_1, obj -> node_2);
            free(path);
        }

        objs = objs -> tail;
    }

    board_t_free(empty);
}

int my_turn(board_t *board, board_t *my_board, float p, float overlap_choice, int forward_view_place, int forward_view_pick, int first_turn)
{
    #ifdef PRINT_DO
    int debug = 1;
    #else
    int debug = 0;
    #endif

    int status;
    if (first_turn)
    {
        if (debug){printf("Prend premier objectif.\n"); fflush(stdout);}
        status = pick_objective(board, my_board, p, overlap_choice, priority_calculation, choose_objective_start);
    }else{

        update_obj(board, my_board);
        
        linked_list_t *paths = path_planning(board, my_board, p, priority_calculation);

        if (board -> objectives == NULL && board -> wagons > 15 && board -> opponent_wagon > 15)
        {
            if (debug){printf("Prend objectif.\n"); fflush(stdout);}
            status = pick_objective(board, my_board, p, overlap_choice, priority_calculation, choose_objective);
        }else{
            int buildable = can_build_something(board, paths, forward_view_place);

            if (buildable == -1)
            {
                if (debug){printf("Prend carte.\n"); fflush(stdout);}
                status = pick_card(board, paths, forward_view_pick, choose_card);
            }else{
                if (debug){printf("Prend chemin.\n"); fflush(stdout);}
                status = build_track(board, my_board, paths, forward_view_place);
            }
        }
    }
    //printBoard();

    return status;
}

/*si 45 wagon et 0 objectif piocher objectif*/
/*calcul chemin*/
/*sur les 2 - 3 prochaine routes :
    - si on peut, on pose
    - sinon on pioche -> dabord en certitude, si rien, blind
*/

/*si on a plus d'objectif, selon mes et enemi wagon on pioche, sinon, on pose des longues routes*/

/*voila*/

/*
besoin :
    -fonction pour decider les objectifs (ok)
    -fonction pour decider les cartes a piocher (ok)
    -fonction qui donne une liste de chemin (ok)
    -fonction priorité pour dijkstra et kruskal (~ok)
    -fonction pour savoir si on peut poser un obj; (ok)
*/

