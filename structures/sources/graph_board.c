#include <stdlib.h>
#include <stdio.h>
#include "../header/linked_list_arete.h"
#include "../header/graph_board.h"

//#define DEBGUG_GRAPH_BOARD

board_t *board_t_init(int nb_node, int cards[4])
{
    board_t *board = malloc(sizeof(board_t));

    if (board == NULL)
    {
        printf("Allocation failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    /*initialisation du graph à NULL*/
    linked_list_t **graph = malloc(sizeof(linked_list_t *) * nb_node);

    if (graph == NULL)
    {
        printf("Allocation failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nb_node; i++)
    {
        graph[i] = NULL;
    }

    /*initialisation des cartes à 0 puis ajout des cartes de début*/
    int *card = malloc(sizeof(int) * 9);

    if (card == NULL)
    {
        printf("Allocation of size int * 9 failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 9; i++)
    {
        card[i] = 0;
    }

    for (int i = 0; i < 4; i++)
    {
        card[cards[i] - 1] += 1;
    }

    board -> graph = graph;
    board -> nb_node = nb_node;
    board -> cards = card;
    board -> wagons = 45;
    board -> opponent_wagons = 45;
    board -> objectives = NULL;

    return board;
}

void board_t_free(board_t *board)
{
    for (int i = 0; i < board -> nb_node; i++)
    {
        edge_list_free(board -> graph[i]);
    }

    objective_list_free(board -> objectives);
    free(board -> graph);
    free(board -> cards);
    free(board);
}

void board_t_add(board_t *board, int node_a, int node_b, int length, int color1, int color2)
{
    edge_list_add(&(board -> graph[node_a]), node_b, color1, color2, length);
    edge_list_add(&(board -> graph[node_b]), node_a, color1, color2, length);
}

void board_t_rm(board_t *board, int node_a, int node_b)
{
    edge_list_rm_node(&(board -> graph[node_a]), node_b);
    edge_list_rm_node(&(board -> graph[node_b]), node_a);
}

#ifdef DEBGUG_GRAPH_BOARD

int main(void)
{
    int card[4]= {1, 2, 3, 4};
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