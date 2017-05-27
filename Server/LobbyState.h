#pragma once

#include "ServerState.h"

class LobbyState : public ServerState {
public:
    virtual void Enter(GameServer* server) override;
    virtual ServerState* HandlePackets(GameServer* server) override;
    virtual void Update(PlayerList* player_list) override;
    virtual void SendUpdates(ServerSocket* socket, const PlayerList& player_list) override;
};
