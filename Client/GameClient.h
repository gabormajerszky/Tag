#pragma once

#include "MainMenu.h"
#include "ConnectMenu.h"
#include "ConnectFailed.h"
#include "Settings.h"
#include "Lobby.h"
#include "Match.h"
#include "Result.h"
#include "Pause.h"

class GameClient {

    friend class MainMenu;
    friend class ConnectMenu;
    friend class ConnectFailed;
    friend class Settings;
    friend class Lobby;
    friend class Match;
    friend class Result;
    friend class Pause;

    MainMenu main_menu;
    ConnectMenu connect_menu;
    ConnectFailed connect_failed;
    Settings settings;
    Lobby lobby;
    Match match;
    Result result;
    Pause pause;

public:
    static const sf::Font& GetFont() { return font; }
    GameClient() : state(&main_menu) { font.loadFromFile("res/captureit.ttf"); }
    void Run();

private:
    static sf::Font font;
    ClientState* state;
};
