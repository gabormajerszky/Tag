#pragma once

#include "ClientState.h"

class MainMenu : public ClientState {
public:
    MainMenu();
    virtual ClientState* HandlePackets(GameClient* game) override;
    virtual ClientState* HandleInput(GameClient* game) override;
    virtual void Render(sf::RenderWindow* window) override;

private:
    std::vector<sf::Text> buttons;
    int active_menu;
};
