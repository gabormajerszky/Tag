#pragma once

#include "ClientState.h"

class SettingsState : public ClientState {

public:

    SettingsState(const sf::VideoMode& vm,
                  const sf::Font& font,
                  const sf::Color& active_color,
                  const sf::Color& inactive_color);

    virtual ClientState* HandlePackets(GameClient* game) override;
    virtual ClientState* HandleInput(GameClient* game) override;
    virtual void Render(GameClient* game) override;

private:

    ClientState* HandleReturn(GameClient* game);
    void HandleUp(GameClient* game);
    void HandleDown(GameClient* game);

    std::vector<sf::Text> buttons;
    int active_menu = 0;

};
