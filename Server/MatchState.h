#pragma once

#include "ServerState.h"

class MatchState : public ServerState {
public:
    virtual void Enter(GameServer* server) override;
    virtual ServerState* HandlePackets(GameServer* server) override;
    virtual void Update(PlayerList* player_list) override;
    virtual void SendUpdates(ServerSocket* socket, const PlayerList& player_list) override;

private:
    sf::Int8 chaser_index;
    sf::Clock last_catch;
    sf::Clock match_timer;
};
