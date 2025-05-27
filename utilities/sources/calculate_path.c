#include <stdlib.h>
#include "../../structures/structures.h"
#include "../utilities.h"


static float just_length(board_t *board, int node_a, int node_b, float p)
{
    return edge_list_get_node(board -> graph[node_a], node_b) -> length;
}

int *calculate_path(board_t *board, board_t *my_board, union_find_t *abrm, int node_a, int node_b)
{
    int *cards = malloc(sizeof(int) * 4);
    for (int i = 0; i < 4; i++)
    {
        cards[i] = 5;
    }

    board_t *empty = board_t_init(1, cards);
    board_t *abrm_to_graph = board_t_init(board -> nb_node, cards);

    free(cards);
    
    for (int i = 0; i < board -> nb_node; i++)
    {
        if (i != abrm -> former[i])
        {
            edge_t *edge = edge_list_get_node(board -> graph[i], abrm -> former[i]);
            if (edge != NULL)
            {
                board_t_add(abrm_to_graph, i, abrm -> former[i], edge -> length, edge -> color1, edge -> color2);
            }

            edge = edge_list_get_node(my_board -> graph[i], abrm -> former[i]);
            if (edge != NULL)
            {
                board_t_add(abrm_to_graph, i, abrm -> former[i], edge -> length, edge -> color1, edge -> color2);
            }
        }
    }

    int *path = dijkstra(empty, abrm_to_graph, node_a, node_b, 1., just_length);

    board_t_free(empty);
    board_t_free(abrm_to_graph);

    return path;
}