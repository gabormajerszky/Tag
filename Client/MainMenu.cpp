#include "MainMenu.h"
#include "GameClient.h"
#include <iostream>


MainMenu::MainMenu() : active_menu(0) {

    buttons.push_back(sf::Text("CONNECT", GameClient::GetFont()));
    buttons.push_back(sf::Text("SETTINGS", GameClient::GetFont()));
    buttons.push_back(sf::Text("EXIT", GameClient::GetFont()));

}


ClientState* MainMenu::HandlePackets(GameClient* game) { return &game->main_menu; }


ClientState* MainMenu::HandleInput(GameClient* game) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {

        std::string label = buttons[active_menu].getString();

        if (label == "CONNECT") {
            return &game->connect_menu;
        }
        else if (label == "SETTINGS") {
            return &game->settings;
        }
        else if (label == "EXIT") {
            // !!! will need to close the window here...
            return &game->main_menu;
        }
        else {
            return &game->main_menu;
        }

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

        active_menu = active_menu + 2 * buttons.size() - 1;
        return &game->main_menu;

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

        active_menu = active_menu + buttons.size() + 1;
        return &game->main_menu;

    }
    else {
        return &game->main_menu;
    }

}


void MainMenu::Render(sf::RenderWindow* window) {

    window->clear();
    for (const auto& button : buttons) {
        window->draw(button);
    }
    window->display();

}
