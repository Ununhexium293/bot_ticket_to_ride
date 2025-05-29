#include <stdlib.h>
#include <stdbool.h>
#include "../../structures/structures.h"
#include "../../utilities/utilities.h"
#include "../../tickettorideapi/ticketToRide.h"

#ifndef STRAT
#define KRUSK 0
#define DIJ 1

#define STRAT KRUSK
#endif

bool *choose_objective(board_t *board, board_t *my_board, Objective *objs, float p, float overlap_choice, float (*priority_calculation)(board_t *, int, int, float))
{
    bool *choosen = malloc(sizeof(bool));

    /*create an empty board*/
    int *cards = malloc(sizeof(int) * 4);
    for (int i = 0; i < 4; i++)
    {
        cards[i] = 5;
    }
    board_t *empty = board_t_init(1, cards);
    free(cards);

    /*check if any objective is impossible*/
    for (int i = 0; i < 3; i++)
    {
        int *path = dijkstra(board, my_board, objs[i].from, objs[i].to, 0., priority_calculation);

        if (path == NULL)
        {
            choosen[i] = false;
        }else {
            free(path);
            choosen[i] = true;
        }
    }

    /*if none are possible, we only take the one with the least amount of score*/
    if (!choosen[1] && !choosen[2] && !choosen[3])
    {
        if (objs[1].score < objs[2].score && objs[1].score < objs[3].score)
        {
            choosen[1] = true;
            return choosen;
        }else if (objs[2].score < objs[3].score)
        {
            choosen[2] = true;
            return choosen;
        }else {
            choosen[3] = true;
            return choosen;
        }
    }

    /*check if any is already completed*/
    bool *done = malloc(sizeof(bool));
    for (int i = 0; i < 3; i++)
    {
        int *path = dijkstra(empty, my_board, objs[i].from, objs[i].to, 0., priority_calculation);

        if (path == NULL)
        {
            done[i] = false;
        }else {
            free(path);
            done[i] = true;
        }
    }
    board_t_free(empty);

    /*check overlap of objectives*/
    int *paths[3];

#if STRAT == KRUSK

    board_t *krusk = kruskal(board, p, priority_calculation);

    for (int i = 0; i < 3; i++)
    {
        paths[i] = calculate_path(board, my_board, krusk, objs[i].from, objs[i].to);
    }

    board_t_free(krusk);

#elif STRAT == DIJ

    for (int i = 0; i < 3; i++)
    {
        paths[i] = dijkstra(board, my_board, objs[i].from, objs[i].to, p, priority_calculation);
    }

#endif

    int lengths[3];
    int nodes_a[3];
    int nodes_b[3];

    for (int i = 0; i < 3; i++)
    {
        lengths[i] = path_length(board, paths[i], objs[i].from, objs[i].to);
        nodes_a[i] = objs[i].from;
        nodes_b[i] = objs[i].to;
    }
    
    int *overlap = path_overlap_length(board, paths, nodes_a, nodes_b);

    //int cost[4];
    //
    //cost[0] = lengths[0] + lengths[1] - overlap[0];
    //cost[1] = lengths[1] + lengths[2] - overlap[1];
    //cost[2] = lengths[2] + lengths[0] - overlap[2];
    //cost[3] = lengths[0] + lengths[1] + lengths[2] - overlap[3]; /*pas correct mais pas de reel moyen d'obtenir*/

    float rapport_overlap_length[4];

    rapport_overlap_length[0] = ((float) overlap[0]) / ((float) (lengths[0] + lengths[1] + 1));
    rapport_overlap_length[1] = ((float) overlap[1]) / ((float) (lengths[1] + lengths[2] + 1));
    rapport_overlap_length[2] = ((float) overlap[2]) / ((float) (lengths[2] + lengths[0] + 1));
    rapport_overlap_length[3] = ((float) overlap[3]) / ((float) (lengths[0] + lengths[1] + lengths[2] + 1));

    float rapport_point_length[3];

    for (int i = 0; i < 3; i++)
    {
        rapport_point_length[i] = ((float) objs[i].score) / ((float) lengths[i]);
    }

    /*selection du premier l'objectif*/

    int rank[3] = {0, 1, 2};

    if (rapport_point_length[0] > rapport_point_length[1] && rapport_point_length[0] > rapport_point_length[2])
    {
        if(rapport_point_length[1] < rapport_point_length[2])
        {
            rank[1] = 2;
            rank[2] = 1;
        }
    }else if(rapport_point_length[0] > rapport_point_length[1])
    {
        rank[0] = 2;
        rank[1] = 0;
        rank[2] = 1;
    }else if (rapport_point_length[0] > rapport_point_length[2])
    {
        rank[0] = 1;
        rank[1] = 0;
    }else {
        if(rapport_point_length[1] < rapport_point_length[2])
        {
            rank[0] = 2;
            rank[1] = 1;
            rank[2] = 0;
        }else
        {
            rank[0] = 1;
            rank[1] = 2;
            rank[2] = 0;
        }
    }

    /*On evite de mettre en premier une route déjà prise*/

    for (int i = 0; i < 2; i++)
    {
        int temp;

        if (done[rank[0]])
        {
            temp = rank[0];
            rank[0] = rank[1];
            rank[1] = rank[2];
            rank[2] = temp;
        }
    }

    /*rank[0] est l'objectif selectinné (avant tri)*/

    if (choosen[rank[0]])
    {
        if (choosen[rank[1]] && choosen[rank[2]] && rapport_overlap_length[3] >= overlap_choice)
        {
            ;
        }else if (choosen[rank[1]] && rapport_overlap_length[0] >= overlap_choice)
        {
            choosen[rank[2]] = false;
        }else if(choosen[rank[2]] && rapport_overlap_length[2] >= overlap_choice){
            choosen[rank[1]] = false;
        }else{
            choosen[rank[1]] = false;
            choosen[rank[2]] = false;
        }
    }else if(choosen[rank[1]])
    {
        if (choosen[rank[2]] && rapport_overlap_length[1] >= overlap_choice)
        {
            ;
        }else{
            choosen[rank[2]] = false;
        }
    }else if(choosen[rank[2]])
    {
        ;
    }else{
        if (objs[rank[0]].score < objs[rank[1]].score && objs[rank[0]].score < objs[rank[2]].score)
        {
            choosen[rank[0]] = true;
        }else if (objs[rank[2]].score < objs[rank[1]].score)
        {
            choosen[rank[2]] = true;
        }else {
            choosen[rank[1]] = true;
        }
    }

    /*on prend les routes déjà faites*/
    for (int i = 0; i < 3; i++)
    {
        if (done[i])
        {
            choosen[i] = true;
        }
    }

    
    
    
    free(done);
    for (int i = 0; i < 3; i++)
    {
        free(paths[i]);
    }
    free(overlap);

    return choosen;
}

bool *choose_objective_start(board_t *board, board_t *my_board, Objective *objs, float p, float overlap_choice, float (*priority_calculation)(board_t *, int, int, float))
{
    bool *choosen = malloc(sizeof(bool));

    for (int i = 0; i < 3; i++)
    {
        choosen[i] = true;
    }

    /*check overlap of objectives*/
    int *paths[3];

#if STRAT == KRUSK

    board_t *krusk = kruskal(board, p, priority_calculation);
    
    for (int i = 0; i < 3; i++)
    {
        paths[i] = calculate_path(board, my_board, krusk, objs[i].from, objs[i].to);
    }
    
    board_t_free(krusk);

#elif STRAT == DIJ

    for (int i = 0; i < 3; i++)
    {
        paths[i] = dijkstra(board, my_board, objs[i].from, objs[i].to, p, priority_calculation);
    }

#endif

    int lengths[3];
    int nodes_a[3];
    int nodes_b[3];

    for (int i = 0; i < 3; i++)
    {
        lengths[i] = path_length(board, paths[i], objs[i].from, objs[i].to);
        nodes_a[i] = objs[i].from;
        nodes_b[i] = objs[i].to;
    }
    
    int *overlap = path_overlap_length(board, paths, nodes_a, nodes_b);

    //int cost[4];
    //
    //cost[0] = lengths[0] + lengths[1] - overlap[0];
    //cost[1] = lengths[1] + lengths[2] - overlap[1];
    //cost[2] = lengths[2] + lengths[0] - overlap[2];
    //cost[3] = lengths[0] + lengths[1] + lengths[2] - overlap[3]; /*pas correct mais pas de reel moyen d'obtenir*/

    float rapport_overlap_length[4];

    rapport_overlap_length[0] = ((float) overlap[0]) / ((float) (lengths[0] + lengths[1] + 1));
    rapport_overlap_length[1] = ((float) overlap[1]) / ((float) (lengths[1] + lengths[2] + 1));
    rapport_overlap_length[2] = ((float) overlap[2]) / ((float) (lengths[2] + lengths[0] + 1));
    rapport_overlap_length[3] = ((float) overlap[3]) / ((float) (lengths[0] + lengths[1] + lengths[2] + 1));

    float rapport_point_length[3];

    for (int i = 0; i < 3; i++)
    {
        rapport_point_length[i] = ((float) objs[i].score) / ((float) lengths[i]);
    }

    /*selection du premier l'objectif*/

    int rank[3] = {0, 1, 2};

    if (rapport_point_length[0] > rapport_point_length[1] && rapport_point_length[0] > rapport_point_length[2])
    {
        if(rapport_point_length[1] < rapport_point_length[2])
        {
            rank[1] = 2;
            rank[2] = 1;
        }
    }else if(rapport_point_length[0] > rapport_point_length[1])
    {
        rank[0] = 2;
        rank[1] = 0;
        rank[2] = 1;
    }else if (rapport_point_length[0] > rapport_point_length[2])
    {
        rank[0] = 1;
        rank[1] = 0;
    }else {
        if(rapport_point_length[1] < rapport_point_length[2])
        {
            rank[0] = 2;
            rank[1] = 1;
            rank[2] = 0;
        }else
        {
            rank[0] = 1;
            rank[1] = 2;
            rank[2] = 0;
        }
    }

    /*rank[0] est le premier objectif selectinné*/

    if (rapport_overlap_length[3] >= overlap_choice)
    {
        ;
    }else if (rapport_overlap_length[0] >= overlap_choice)
    {
        choosen[rank[2]] = false;
    }else if(rapport_overlap_length[2] >= overlap_choice)
    {
        choosen[rank[1]] = false;
    }else{
        choosen[rank[2]] = false;
    }
    
    for (int i = 0; i < 3; i++)
    {
        free(paths[i]);
    }
    free(overlap);

    return choosen;
}