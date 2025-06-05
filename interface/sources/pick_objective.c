#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../header/pick_objective.h"

static Objective *draw(void)
{
    MoveData *data = malloc(sizeof(MoveData));
    if (data == NULL)
    {
        printf("Allocation failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    MoveResult *move = malloc(sizeof(MoveResult));
    if (move == NULL)
    {
        printf("Allocation failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    data -> action = DRAW_OBJECTIVES;

    ResultCode send_move_result = sendMove(data, move);

    if (send_move_result != ALL_GOOD || move -> state != NORMAL_MOVE)
    {
        return NULL;
    }

    if (move -> opponentMessage != NULL)
    {
        printf("opponent message :\n");
        printf(move -> opponentMessage);
        printf("\n");
        free(move -> opponentMessage);
    }

    if (move -> message != NULL)
    {
        printf("opponent message :\n");
        printf(move -> message);
        printf("\n");
        free(move -> message);
    }

    Objective *obj = malloc(sizeof(Objective) * 3);
    for (int i = 0; i < 3; i++)
    {
        obj[i] = move -> objectives[i];
    }

    free(move);
    free(data);
    
    return obj;
}

static int choose(bool *obj)
{
    MoveData *data = malloc(sizeof(MoveData));
    if (data == NULL)
    {
        printf("Allocation failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    MoveResult *move = malloc(sizeof(MoveResult));
    if (move == NULL)
    {
        printf("Allocation failure in file %s, function %s, line %d\n", __FILE__, __func__, __LINE__);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    data -> action = CHOOSE_OBJECTIVES;
    for (int i = 0; i < 3; i++)
    {
        data -> chooseObjectives[i] = obj[i];
    }

    ResultCode send_move_result = sendMove(data, move);

    if (send_move_result != ALL_GOOD)
    {
        return EXIT_FAILURE;
    }

    if (move -> opponentMessage != NULL)
    {
        printf("opponent message :\n");
        printf(move -> opponentMessage);
        printf("\n");
        free(move -> opponentMessage);
    }

    if (move -> message != NULL)
    {
        printf("opponent message :\n");
        printf(move -> message);
        printf("\n");
        free(move -> message);
    }

    int state = move -> state;

    free(move);
    free(data);

    return state;
}

/*________________________________________________________________________________________________________________*/

int pick_objective(board_t *board, board_t *my_board, float p, float overlap_choice, float (*priority_calculation_)(board_t *, int, int, float), bool *(*choose_objective)(board_t *, board_t *, Objective *, float, float , float (*priority_calculation)(board_t *, int, int, float)))
{
    Objective *obj = draw();

    if(obj == NULL)
    {
        return EXIT_FAILURE;
    }

    bool *obj_choosen = choose_objective(board, my_board, obj, p, overlap_choice, priority_calculation_);

    int state = choose(obj_choosen);

    for (int i = 0; i < 3; i++)
    {
        int ind = -1;
        int big = 0;
        for (int j = 0; j < 3; j++)
        {
            if (obj_choosen[j] && obj[j].score > big)
            {
                ind = j;
                big = obj[j].score;
            }
        }

        if (ind != -1)
        {
            objective_list_add(&(board -> objectives), obj[ind].from, obj[ind].to, obj[ind].score);
        }

        obj_choosen[ind] = false;
    }

    free(obj);

    free(obj_choosen);

    return state;
}