#include "ConnectFailed.h"
#include "GameClient.h"


ClientState* ConnectFailed::HandlePackets(GameClient* game) { return &game->connect_failed; }

ClientState* ConnectFailed::HandleInput(GameClient* game) { return &game->connect_failed; }

void ConnectFailed::Render(GameClient* game) {}
