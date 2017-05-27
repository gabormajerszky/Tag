#include "ConnectMenu.h"
#include "GameClient.h"


ClientState* ConnectMenu::HandlePackets(GameClient* game) { return &game->connect_menu; }

ClientState* ConnectMenu::HandleInput(GameClient* game) { return &game->connect_menu; }

void ConnectMenu::Render(sf::RenderWindow* window) {}