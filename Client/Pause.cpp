#include "Pause.h"
#include "GameClient.h"


ClientState* Pause::HandlePackets(GameClient* game) { return &game->pause; }

ClientState* Pause::HandleInput(GameClient* game) { return &game->pause; }

void Pause::Render(sf::RenderWindow* window) {}
