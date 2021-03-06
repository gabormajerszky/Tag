#include "MainMenu.h"
#include "GameClient.h"
#include <iostream>


MainMenu::MainMenu(const sf::VideoMode& vm,
                   const sf::Font& font,
                   const sf::Color& active_color,
                   const sf::Color& inactive_color) {

    unsigned int character_size = 90;
    float line_spacing = 90.0f;

    buttons.push_back(sf::Text("CONNECT", font, character_size));
    buttons.push_back(sf::Text("SETTINGS", font, character_size));
    buttons.push_back(sf::Text("EXIT", font, character_size));

    sf::Vector2f scale;
    scale.x = static_cast<float>(vm.width) / GameConst::NATIVE_WIDTH;
    scale.y = static_cast<float>(vm.height) / GameConst::NATIVE_HEIGHT;

    float WIDTH = scale.x * GameConst::NATIVE_WIDTH;
    float HEIGHT = scale.y * GameConst::NATIVE_HEIGHT;

    // There's one less "line spacing" then buttons
    float menu_height = -line_spacing;
    for (auto& btn : buttons) {
        menu_height += btn.getGlobalBounds().height + line_spacing;
    }

    float current_height = (HEIGHT - menu_height) / 2;

    for (auto& btn : buttons) {

        float width = btn.getGlobalBounds().width;
        float height = btn.getGlobalBounds().height;

        btn.setScale(scale);
        btn.setOrigin(width / 2, 0);
        btn.move(WIDTH / 2, current_height);
        btn.setFillColor(inactive_color);

        current_height += height + line_spacing;

    }

    buttons[active_menu].setFillColor(active_color);

}


ClientState* MainMenu::HandlePackets(GameClient* game) { return &game->main_menu; }


ClientState* MainMenu::HandleInput(GameClient* game) {

    sf::Event menu_event;
    while (game->window.pollEvent(menu_event)) {

        if (menu_event.type == sf::Event::KeyPressed) {

            switch (menu_event.key.code) {

                case sf::Keyboard::Return:
                    return HandleReturn(game);

                case sf::Keyboard::Up:
                    HandleUp(game);
                    return &game->main_menu;

                case sf::Keyboard::Down:
                    HandleDown(game);
                    return &game->main_menu;

                default:
                    return &game->main_menu;

            }

        }

    }

    return &game->main_menu;

}


void MainMenu::Render(GameClient* game) {

    game->window.clear();
    game->window.draw(game->menu_background);
    for (const auto& button : buttons) {
        game->window.draw(button);
    }
    game->window.display();

}


ClientState* MainMenu::HandleReturn(GameClient* game) {

    std::string label = buttons[active_menu].getString();

    if (label == "CONNECT") {
        return &game->connect_menu;
    }
    else if (label == "SETTINGS") {
        return &game->settings_state;
    }
    else if (label == "EXIT") {
        game->window.close();
        return &game->main_menu;
    }
    else {
        return &game->main_menu;
    }

}


void MainMenu::HandleUp(GameClient* game) {

    buttons[active_menu].setFillColor(game->inactive_color);
    active_menu = (active_menu + buttons.size() - 1) % buttons.size();
    buttons[active_menu].setFillColor(game->active_color);

}


void MainMenu::HandleDown(GameClient* game) {

    buttons[active_menu].setFillColor(game->inactive_color);
    active_menu = (active_menu + 1) % buttons.size();
    buttons[active_menu].setFillColor(game->active_color);

}
