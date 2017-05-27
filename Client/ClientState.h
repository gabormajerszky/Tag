#pragma once

#include <SFML\Graphics.hpp>

class GameClient;

class ClientState {
public:
    virtual ClientState* HandlePackets(GameClient* game) = 0;
    virtual ClientState* HandleInput(GameClient* game) = 0;
    virtual void Render(sf::RenderWindow* window) = 0;
};
