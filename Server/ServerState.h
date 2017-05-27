#pragma once

#include "AddressedPacket.h"
#include "PlayerList.h"
#include "ServerSocket.h"

class GameServer;

class ServerState {
public:
    virtual void Enter(GameServer* server) = 0;
    virtual ServerState* HandlePackets(GameServer* server) = 0;
    virtual void Update(PlayerList* player_list) = 0;
    virtual void SendUpdates(ServerSocket* socket, const PlayerList& player_list) = 0;
};
