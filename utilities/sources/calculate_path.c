#include <stdio.h>
#include <stdlib.h>
#include "../../structures/structures.h"
#include "../utilities.h"

#ifndef STRAT
#define KRUSK 0
#define DIJ 1

#define STRAT KRUSK
#endif

static float just_length(board_t *board, int node_a, int node_b, float p)
{
    return edge_list_get_node(board -> graph[node_a], node_b) -> length;
}

//int *calculate_path(board_t *board, board_t *my_board, union_find_t *abrm, int node_a, int node_b)
//{
//    int *cards = malloc(sizeof(int) * 4);
//    for (int i = 0; i < 4; i++)
//    {
//        cards[i] = 5;
//    }
//
//    board_t *empty = board_t_init(board -> nb_node, cards);
//    board_t *abrm_to_graph = board_t_init(board -> nb_node, cards);
//
//    //free(cards);
//
//    /*debug*/
//    for (int i = 0; i < board -> nb_node; i++)
//    {
//        printf("%d : %d, ", i, abrm -> parent[i]);
//    }
//    printf("\n");
//    fflush(stdout);
//    
//    for (int i = 0; i < board -> nb_node; i++)
//    {
//        if (i != abrm -> parent[i])
//        {
//            edge_t *edge = edge_list_get_node(board -> graph[i], abrm -> parent[i]);
//            if (edge != NULL)
//            {
//                board_t_add(abrm_to_graph, i, abrm -> parent[i], edge -> length, edge -> color1, edge -> color2);
//            }
//
//            edge = edge_list_get_node(my_board -> graph[i], abrm -> parent[i]);
//            if (edge != NULL)
//            {
//                board_t_add(abrm_to_graph, i, abrm -> parent[i], edge -> length, edge -> color1, edge -> color2);
//            }
//        }
//    }
//
//    int *path = dijkstra(empty, abrm_to_graph, node_a, node_b, 1., just_length);
//
//    board_t_free(empty);
//    board_t_free(abrm_to_graph);
//
//    return path;
//}

int *calculate_path(board_t *board, board_t *my_board, board_t *abrm, int node_a, int node_b)
{
    int *cards = malloc(sizeof(int) * 4);
    for (int i = 0; i < 4; i++)
    {
        cards[i] = 5;
    }

    board_t *empty = board_t_init(board -> nb_node, cards);
    free(cards);


    int *path = dijkstra(empty, abrm, node_a, node_b, 1., just_length);

    board_t_free(empty);

    return path;
}

static void add_path_to_list(board_t *board, linked_list_t **list, int *path, int node_a, int node_b)
{
    for (int i = node_b; i != node_a; i = path[i])
    {
        edge_t *edge = edge_list_get_node(board -> graph[i], path[i]);

        if (edge != NULL)
        {
            objective_list_add(list, i, path[i], 0);
        }
    }

    free(path);
}

linked_list_t *path_planning(board_t *board, board_t *my_board, float p, float (*priority_calculation)(board_t *, int, int, float))
{
    linked_list_t *obj = board -> objectives;

    #if STRAT == KRUSK
    board_t *krusk = kruskal(board, my_board, p, priority_calculation);
    #endif

    linked_list_t *plan = NULL;

    while (obj != NULL)
    {
        int node_a = ((objective_t *) obj -> head) -> node_1;
        int node_b = ((objective_t *) obj -> head) -> node_2;
        
        #if STRAT == KRUSK
        add_path_to_list(board, &plan, calculate_path(board, my_board, krusk, node_a, node_b), node_a, node_b);
        #elif STRAT == DIJ
        add_path_to_list(board, &plan, dijkstra(board, my_board, node_a, node_b, p, priority_calculation), node_a, node_b);
        #endif
        obj = obj -> tail;
    }

    #if STRAT == KRUSK
    board_t_free(krusk);
    #endif

    return plan;
}