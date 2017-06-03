#pragma once

#include "ClientState.h"

class ConnectMenu : public ClientState {
public:
    virtual ClientState* HandlePackets(GameClient* game) override;
    virtual ClientState* HandleInput(GameClient* game) override;
    virtual void Render(GameClient* game) override;
};
