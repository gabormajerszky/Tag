#include "Match.h"
#include "GameClient.h"


ClientState* Match::HandlePackets(GameClient* game) { return &game->match; }

ClientState* Match::HandleInput(GameClient* game) { return &game->match; }

void Match::Render(GameClient* game) {}
