#ifndef DIS_CONNECT_H
#define DIS_CONNECT_H

#include "../../tickettorideapi/ticketToRide.h"

GameData *connect_bot(const char *bot_name, const char *setting);

void disconnect_bot(GameData *data);

#endif