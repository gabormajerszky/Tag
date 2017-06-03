#include "Lobby.h"
#include "GameClient.h"


ClientState* Lobby::HandlePackets(GameClient* game) { return &game->lobby; }

ClientState* Lobby::HandleInput(GameClient* game) { return &game->lobby; }

void Lobby::Render(GameClient* game) {}
