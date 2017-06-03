#pragma once

#include "ClientSocket.h"
#include "State.h"

class GameClient {

    friend class MainMenu;
    friend class ConnectMenu;
    friend class ConnectFailed;
    friend class SettingsState;
    friend class Lobby;
    friend class Match;
    friend class Result;
    friend class Pause;

    MainMenu main_menu;
    ConnectMenu connect_menu;
    ConnectFailed connect_failed;
    SettingsState settings_state;
    Lobby lobby;
    Match match;
    Result result;
    Pause pause;

public:

    GameClient(const sf::VideoMode& vm,
               const sf::Font& font,
               const sf::Texture& menu_texture,
               const sf::Color& active_color,
               const sf::Color& inactive_color,
               const Address& address);

    void Run();

private:

    ClientState* state;
    sf::RenderWindow window;
    sf::Sprite menu_background;
    sf::Color active_color;
    sf::Color inactive_color;
    ClientSocket socket;

};
