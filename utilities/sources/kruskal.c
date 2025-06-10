#include <stdlib.h>
#include <stdio.h>
#include "../header/kruskal.h"
#include "../header/dijkstra.h"
#include "../../structures/header/union_find.h"
#include "../../structures/header/priority_queue_node.h"
#include "../../structures/header/graph_board.h"

#ifndef UPGRADE
#define UPGRADE
#endif

static float just_length(board_t *board, int node_a, int node_b, float p)
{
    return edge_list_get_node(board -> graph[node_a], node_b) -> length;
}

static p_queue_t *graph_to_queue(board_t *board, board_t *my_board, float p, float (*priority_calculation)(board_t *board, int node_a, int node_b, float p))
{

    #ifdef UPGRADE

    /*On a au plus 3 objectif en meme temps*/
    linked_list_t *obj = board -> objectives;
    int *paths;
    int used[board -> nb_node][board -> nb_node];

    for (int i = 0; i < board -> nb_node; i++)
    {
        for (int j = 0; j < board -> nb_node; j++)
        {
            used[i][j] = 0;
        }
    }

    for (int i = 0; i < 3 && obj !=NULL; i++)
    {
        int node_a = ((objective_t *) obj -> head) -> node_1;
        int node_b = ((objective_t *) obj -> head) -> node_2;

        paths = dijkstra(board, my_board,  node_a, node_b, p, just_length);

        for (int j = node_b; j != node_a; j = paths[j])
        {
            used[j][paths[j]] += 1;
            used[j][paths[j]] += 1;
        }

        free(paths);
    }
    
    #endif
    
    int **path_added = malloc(sizeof(int *) * board -> nb_node);

    for (int i = 0; i < board -> nb_node; i++)
    {
        path_added[i] = malloc(sizeof(int) * board -> nb_node);
        for (int j = 0; j < board -> nb_node; j++)
        {
            path_added[i][j] = 1;
        }
    }

    p_queue_t *queue = NULL;

    for (int i = 0; i < board -> nb_node; i++)
    {
        linked_list_t *list = board -> graph[i];
        while (list != NULL)
        {
            edge_t *edge = edge_list_head(list);
            if (path_added[edge -> node][i])
            {
                path_added[edge -> node][i] = 0;
                path_added[i][edge -> node] = 0;

                #ifdef UPGRADE
                node_p_queue_push(&queue, i, edge -> node, priority_calculation(board, i, edge -> node, p) - (p * edge ->length * used[i][edge -> node]), 0);
                #else
                node_p_queue_push(&queue, i, edge -> node, priority_calculation(board, i, edge -> node, p), 0);
                #endif
            }
            
            list = list -> tail;
        }

        list = my_board -> graph[i];
        while(list != NULL)
        {
            edge_t *edge = edge_list_head(list);
            if (path_added[edge -> node][i])
            {
                path_added[edge -> node][i] = 0;
                path_added[i][edge -> node] = 0;

                node_p_queue_push(&queue, i, edge -> node, ~0, 0);
            }

            list = list -> tail;
        }
    }

    for  (int i = 0; i < board -> nb_node; i++)
    {
        free(path_added[i]);
    }
    free(path_added);

    return queue;
}

board_t *kruskal(board_t *board, board_t *my_board, float p, float (*priority_calculation)(board_t *board, int node_a, int node_b, float p))
{
    int *cards = malloc(sizeof(int) * 4);
    for (int i = 0; i < 4; i++)
    {
        cards[i] = 5;
    }
    board_t *abrm = board_t_init(board -> nb_node, cards);

    union_find_t *arm = union_find_t_init(board -> nb_node);
    p_queue_t *queue = graph_to_queue(board, my_board, p, priority_calculation);

    while (queue != NULL)
    {
        double_node_t *nodes = node_p_queue_pull(&queue);

        union_find_t_union(arm, abrm, nodes -> node, nodes -> parent);
    }

    union_find_t_free(arm);
    node_p_queue_free(queue);
    
    return abrm;
}