#include <stdlib.h>
#include "../header/get_point.h"
#include "../../structures/header/graph_board.h"

float priority_calculation(board_t *board, int node_a, int node_b, float p)
{
    edge_t *edge = edge_list_get_node(board -> graph[node_a], node_b);
    float length = (float) edge -> length;
    float points = (float) point(edge -> length);

    float priority = p * length + (1. - p) * (16. - points);

    return priority;
}