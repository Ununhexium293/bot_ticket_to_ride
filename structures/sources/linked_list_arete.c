#include "../header/linked_list_arete.h"

//#define DEBUG

edge_t *edge_t_init(int node, int color, int length){
    edge_t *edge = malloc(sizeof(edge_t));

    if (edge == NULL){
        printf("Allocation of size edge_t failed.\n");
        exit(EXIT_FAILURE);
    }

    edge -> node = node;
    edge -> color = color;
    edge -> length = length;

    return edge;
}