#include "../header/dis_connect.h"
#include <stdio.h>
#include <stdlib.h>

GameData *connect_bot(const char *bot_name, const char *setting)
{
    int connect = connectToCGS("82.29.170.160", 15001, bot_name);
    if (connect != ALL_GOOD)
    {
        return NULL;
    }

    GameData *data = malloc(sizeof(GameData));
    if(data == NULL)
    {
        return NULL;
    }

    int sendgamesetting_deb = sendGameSettings(setting, data);
    
    if (sendgamesetting_deb != ALL_GOOD)
    {
        return NULL;
    }

    return data;
}

void disconnect_bot(GameData *data)
{
    quitGame();

    free(data -> trackData);
    free(data -> gameName);
    free(data);
}