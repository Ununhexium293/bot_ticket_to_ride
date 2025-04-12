#include "../header/linked_list_objective.h"
#include <stdlib.h>
#include <stdio.h>

void objective_list_add(linked_list_t **list, int node_1, int node_2, int point)
{
    objective_t *objec = malloc(sizeof(objective_t));
    if (objec == NULL)
    {
        printf("Allocation failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    objec -> node_1 = node_1;
    objec -> node_2 = node_2;
    objec -> point = point;

    linked_list_t_add(list, objec);
}

static int obj_is_equal(void *a, void *b)
{
    objective_t *objec_a = (objective_t *) a;
    objective_t *objec_b = (objective_t *) b;

    return objec_a -> node_1 == objec_b -> node_1 && objec_a -> node_2 == objec_b -> node_2;
}

void objective_list_rm(linked_list_t **list, int node_1, int node_2)
{
    objective_t *objec = malloc(sizeof(objective_t));
    if (objec == NULL)
    {
        printf("Allocation failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    objec -> node_1 = node_1;
    objec -> node_2 = node_2;

    linked_list_t_rm(list, objec, obj_is_equal, free);
}

void objective_list_free(linked_list_t *list)
{
    linked_list_t_free(list, free);
}

static void obj_print(void *obj)
{
    objective_t *objec = (objective_t *) obj;
    printf("node 1 : %d <-> node 2 : %d | point : %d\n", objec -> node_1, objec -> node_2, objec -> point); 
}

void objective_list_print(linked_list_t *list)
{
    linked_list_t_print(list, obj_print);
}