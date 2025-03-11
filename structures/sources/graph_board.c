#include <stdlib.h>
#include <stdio.h>
#include "../header/linked_list_arete.h"
#include "../header/graph_board.h"

#define DEBGUG_GRAPH_BOARD

board_t *board_t_init(int nb_node)
{
    board_t *board = malloc(sizeof(board_t));

    if (board == NULL)
    {
        printf("Allocation of size board_t failed.\n");
        exit(EXIT_FAILURE);
    }

    edge_list_t **graph = malloc(sizeof(edge_list_t *) * nb_node);

    if (graph == NULL)
    {
        printf("Allocation of size edge_list_t * x nb_node failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nb_node; i++)
    {
        graph[i] = NULL;
    }

    board -> graph = graph;
    board -> nb_node = nb_node;

    return board;
}

void board_t_free(board_t *board)
{
    for (int i = 0; i < board -> nb_node; i++)
    {
        edge_list_t_free(board -> graph[i]);
    }

    free(board -> graph);
    free(board);
}

void board_t_add(board_t *board, int node_a, int node_b, int length, int color1, int color2)
{
    edge_list_t_add(&(board -> graph[node_a]), node_b, color1, color2, length);
    edge_list_t_add(&(board -> graph[node_b]), node_a, color1, color2, length);
}

void board_t_rm(board_t *board, int node_a, int node_b)
{
    edge_list_t_rm_node(&(board -> graph[node_a]), node_b);
    edge_list_t_rm_node(&(board -> graph[node_b]), node_a);
}

#ifdef DEBGUG_GRAPH_BOARD

int main(void)
{
    /*test init and free*/

        board_t *test_board_0 = board_t_init(31415);

        board_t_free(test_board_0);

    /*end test init and free*/

    /*test add and rm*/

    board_t *test_board_1 = board_t_init(31415);

    board_t_add(test_board_1, 3, 314, 15, 2, 0);
    board_t_add(test_board_1, 31, 3141, 15, 2, 0);
    board_t_add(test_board_1, 314, 0, 15, 2, 0);
    board_t_add(test_board_1, 1, 2, 15, 2, 0);
    board_t_add(test_board_1, 2, 3, 15, 2, 0);
    board_t_add(test_board_1, 3, 5, 15, 2, 0);
    board_t_add(test_board_1, 5, 8, 15, 2, 0);
    board_t_add(test_board_1, 8, 13, 15, 2, 0);
    board_t_add(test_board_1, 13, 21, 15, 2, 0);
    board_t_add(test_board_1, 21, 34, 15, 2, 0);
    board_t_add(test_board_1, 34, 55, 15, 2, 0);
    board_t_add(test_board_1, 55, 89, 15, 2, 0);

    board_t_rm(test_board_1, 1, 2);

    board_t_free(test_board_1);

    /*end test add and rm*/
}

#endif