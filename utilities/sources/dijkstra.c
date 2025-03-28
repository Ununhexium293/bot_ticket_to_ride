#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../header/dijkstra.h"
#include "../header/priority_calc.h"
#include "../../structures/header/priority_queue_node.h"

int *dijkstra(board_t *board, board_t *my_board, int node_a, int node_b, float proportion)
{
    int seen[board -> nb_node];
    int *parent = malloc(sizeof(int) * board -> nb_node);

    if (parent == NULL)
    {
        printf("Allocation of size int * nb_node failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < board -> nb_node; i++)
    {
        seen[i] = 0;
    }

    p_queue_t *queue = NULL;

    node_p_queue_push(&queue, node_a, -1, 0.);

    while (!seen[node_b] && queue != NULL)
    {
        float priority = *((float *) queue -> priority);
        double_node_t *nodes = node_p_queue_pull(&queue);

        if (!seen[nodes -> node])
        {

            parent[nodes -> node] = nodes -> parent;

            seen[nodes -> node] = 1;

            /*available*/
            linked_list_t *list = board -> graph[nodes -> node];
            while (list != NULL)
            {
                if (!seen[edge_list_head(list) -> node])
                {
                    /*Here the priority is calculated with a combination of the length and the point of the path*/
                    node_p_queue_push(&queue, edge_list_head(list) -> node, nodes -> node, priority + priority_calculation(board, nodes -> node, edge_list_head(list) -> node, proportion));
                }

                list = list -> tail;
            }

            /*already own by me*/
            list = my_board -> graph[nodes -> node];
            while (list != NULL)
            {
                if (!seen[edge_list_head(list) -> node])
                {
                    /*Here the priority is calculated with the length only because we already own the path*/
                    node_p_queue_push(&queue, edge_list_head(list) -> node, nodes -> node, priority);
                } 

                list = list -> tail;
            }
        }
        free(nodes);
    }

    node_p_queue_free(queue);

    if (seen[node_b])
    {
        return parent;
    }else{
        return NULL;
    }
}