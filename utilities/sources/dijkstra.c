#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../header/dijkstra.h"
#include "../../structures/header/priority_queue_node.h"

static int point(int length)
{
    switch(length)
    {
        case 1 : return 1;
        case 2 : return 2;
        case 3 : return 4;
        case 4 : return 7;
        case 5 : return 10;
        case 6 : return 15;
        default : 
            printf("Chemin trop long : %d\n", length);
            exit(EXIT_FAILURE);
    }
}

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

    node_p_queue_t_add(&queue, node_a, -1, 0);

    while (!seen[node_b] && queue != NULL)
    {
        if (!seen[queue -> node])
        {

            parent[queue -> node] = queue -> parent;

            seen[queue -> node] = 1;

            /*available*/
            linked_list_t *list = board -> graph[queue -> node];
            while (list != NULL)
            {
                if (!seen[edge_list_head(list) -> node])
                {
                    /*Here the priority is calculated with a combination of the length and the point of the path*/
                    node_p_queue_t_add(&queue, edge_list_head(list) -> node, queue -> node, queue -> priority + (proportion * ((float) edge_list_head(list) -> length)) + ((1. - proportion) * (16 - ((float) point(edge_list_head(list) -> length)))));
                }

                list = list -> tail;
            }

            /*already own by me*/
            list = my_board -> graph[queue -> node];
            while (list != NULL)
            {
                if (!seen[edge_list_head(list) -> node])
                {
                    /*Here the priority is calculated with the length only because we already own the path*/
                    node_p_queue_t_add(&queue, edge_list_head(list) -> node, queue -> node, queue -> priority);
                } 

                list = list -> tail;
            }

            ///*test*/
            //for (int i = 0; i < board -> nb_node; i++)
            //{
            //    printf("%d ", seen[i]);
            //}
            //printf("\n%d\n", queue -> node);
            //for (int i = 0; i < board -> nb_node; i++)
            //{
            //    printf("%d ", parent[i]);
            //}
            //printf("\n\n\n");
            //fflush(stdout);
        }

        node_p_queue_t_rm(&queue);
    }

    node_p_queue_t_free(queue);

    if (seen[node_b])
    {
        return parent;
    }else{
        return NULL;
    }
}