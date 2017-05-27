#include "Settings.h"
#include "GameClient.h"


ClientState* Settings::HandlePackets(GameClient* game) { return &game->settings; }

ClientState* Settings::HandleInput(GameClient* game) { return &game->settings; }

void Settings::Render(sf::RenderWindow* window) {}