#include <stdlib.h>
#include "bot/header/bot.h"

int main(int argc, char **argv)
{

    float p = 0.5;
    float overlap_choice = 0.9;
    int forward_view_place = 2;
    int forward_view_pick = 5;
    bot("TRAINING NICE_BOT timeout=120 map=USA", argv[1], p, overlap_choice, forward_view_place, forward_view_pick);// seed=385158 seed=2612014 seed=6725371 seed=6928575 seed=7033293
    return EXIT_SUCCESS;
}