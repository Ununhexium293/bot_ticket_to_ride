#ifndef UNION_FIND_H
#define UNION_FIND_H

typedef struct {
    int *former;
    int *rank;
    int nb_node;
}union_find_t;

union_find_t *union_find_t_init(int nb_node);

void union_find_t_union(union_find_t *arm, int node_a, int node_b);

int union_find_t_find(union_find_t *arm, int node);

void union_find_t_free(union_find_t *arm);

#endif