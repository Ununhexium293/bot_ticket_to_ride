#include <stdlob.h>
#include <stdio.h>
#include "../header/get_point.h"
#include "../header/kruskal.h"
#include "../../structures/header/union_find.h"
#include "../../structures/header/priority_queue_node.h"
#include "../../structures/header/graph_board.h"

static p_queue_t *graph_to_queue(board_t *board, float p)
{
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

                node_p_queue_push(&queue, i, edge -> node, priority_calculation(board, i, edge -> node, p));
                list = list -> tail;
            }
        }
    }

    for  (int i = 0; i < board -> nb_node; i++)
    {
        free(path_added[i]);
    }
    free(path_added);

    return queue;
}

int *kruskal(board_t *board, float p)
{
    union_find_t *arm = union_find_t_init(board -> nb_node);
    p_queue_t *queue = graph_to_queue(board, p);

    while (queue != NULL)
    {
        double_node_t *nodes = node_p_queue_pull(&queue);

        union_find_t_union(arm, nodes -> node, nodes -> parent);
    }

    return_tab = arm -> former;

    free(arm -> rank);
    free(arm);

    return arm;
}