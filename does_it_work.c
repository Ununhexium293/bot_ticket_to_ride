#ifndef STRAT
#define KRUSK 0
#define UPGRADE
#define DIJ 1

#define STRAT DIJ
#endif

#include <stdlib.h>
#include "bot/header/bot.h"



extern int DEBUG_LEVEL;
#define DEBUG_CONNECT
//#define DEBUG_HOME

int main(int argc, char **argv)
{
    float p = 0.5;
    float overlap_choice = 0.9;
    int forward_view_place = 1;
    int forward_view_pick = 10;
    bot("TRAINING NICE_BOT timeout=120 map=USA seed=687738", "bot_quentin_LV", p, overlap_choice, forward_view_place, forward_view_pick);// seed=385158 seed=2612014 seed=6725371 seed=6928575 seed=7033293
    return EXIT_SUCCESS;
}