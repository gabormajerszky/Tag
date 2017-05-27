#pragma once

#include "ServerState.h"

class IdleState : public ServerState {
public:
    virtual void Enter(GameServer* server) override;
    virtual ServerState* HandlePackets(GameServer* server) override;    
};
