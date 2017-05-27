#include "Result.h"
#include "GameClient.h"


ClientState* Result::HandlePackets(GameClient* game) { return &game->result; }

ClientState* Result::HandleInput(GameClient* game) { return &game->result; }

void Result::Render(sf::RenderWindow* window) {}
