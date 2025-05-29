#include <stdlib.h>
#include <stdio.h>
#include "../header/path_length.h"
#include "../../structures/structures.h"

int path_length(board_t *board, int *path, int node_a, int node_b)
{
    int length = 0;

    /*debug*/
    for (int i = 0; i < board -> nb_node; i++)
    {
        printf("%d : %d, ", i, path[i]);
    }
    printf("\n");
    fflush(stdout);

    for (int i = node_b; i != node_a; i = path[i])
    {
        edge_t *edge = edge_list_get_node(board -> graph[i], path[i]);
        if (edge != NULL)
        {
            length += edge -> length;
        }
    }

    return length;
}

static int two_path_overlap(board_t *board, int **path, int *node_a, int *node_b, int first, int second)
{
    int length = 0;
    
    for (int i = node_b[first]; i != node_a[first]; i = path[first][i])
    {
        for (int j = node_b[second]; j != node_a[second]; j = path[second][j])
        {
            if (i == j && path[first][i] == path[second][j])
            {
                edge_t *edge = edge_list_get_node(board -> graph[i], path[first][i]);
                if (edge != NULL)
                {
                    length += edge -> length;
                }
            }
        }
    }

    return length;
}

int *path_overlap_length(board_t *board, int **path, int *node_a, int *node_b)
{
    int *lengths = malloc(sizeof(int) * 4);

    lengths[0] = two_path_overlap(board, path, node_a, node_b, 0, 1);
    lengths[1] = two_path_overlap(board, path, node_a, node_b, 1, 2);
    lengths[2] = two_path_overlap(board, path, node_a, node_b, 2, 0);

    lengths[3] = 0;
    
    for (int i = node_b[0]; i != node_a[0]; i = path[0][i])
    {
        for (int j = node_b[1]; j != node_a[1]; j = path[1][j])
        {
            int ok = 1;

            if (i == j && path[0][i] == path[1][j])
            {
                if (i == j && path[0][i] == path[1][j])
                {
                    edge_t *edge = edge_list_get_node(board -> graph[i], path[0][i]);
                    if (edge != NULL)
                    {
                        lengths[3] += edge -> length;
                    }
                }

                ok = 0;
            }

            for (int k = node_b[2]; k != node_a[2]; k = path[2][k])
            {
                if (i == k && path[0][i] == path[2][k] && ok)
                {
                    edge_t *edge = edge_list_get_node(board -> graph[i], path[0][i]);
                    if (edge != NULL)
                    {
                        lengths[3] += edge -> length;
                    }
                    
                    ok = 0;
                }

                if (j == k && path[1][j] == path[2][k] && ok)
                {
                    edge_t *edge = edge_list_get_node(board -> graph[j], path[1][j]);
                    if (edge != NULL)
                    {
                        lengths[3] += edge -> length;
                    }
                }
            }
        }
    }

    return lengths;
}