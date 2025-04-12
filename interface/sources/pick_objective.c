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

    if (send_move_result != ALL_GOOD || move -> state != NORMAL_MOVE)
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

    free(move);
    free(data);

    return EXIT_SUCCESS;
}

/*________________________________________________________________________________________________________________*/

int pick_objective(board_t *board, bool *(*choose_objective)(Objective *))
{
    Objective *obj = draw();

    if(obj == NULL)
    {
        return EXIT_FAILURE;
    }

    bool *obj_choosen = choose_objective(obj);

    for (int i = 0; i < 3; i++)
    {
        if (obj_choosen[i])
        {
            objective_list_add(&(board -> objectives), obj[i].from, obj[i].to, obj[i].score);
        }
    }

    free(obj);
    if (choose(obj_choosen) == EXIT_FAILURE)
    {
        free(obj_choosen);
        return EXIT_FAILURE;
    }
    free(obj_choosen);

    return EXIT_SUCCESS;
}