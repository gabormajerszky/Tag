#include "SettingsState.h"
#include "GameClient.h"

SettingsState::SettingsState(const sf::VideoMode& vm,
                             const sf::Font& font,
                             const sf::Color& active_color,
                             const sf::Color& inactive_color) {

    unsigned int character_size = 60;
    float line_spacing = 60.0f;

    buttons.push_back(sf::Text("NAME", font, character_size));
    buttons.push_back(sf::Text("COLOR", font, character_size));
    buttons.push_back(sf::Text("VOLUME", font, character_size));
    buttons.push_back(sf::Text("HUD POSITION", font, character_size));    
    buttons.push_back(sf::Text("SHOW FPS", font, character_size));
    buttons.push_back(sf::Text("BACK TO MAIN MENU", font, character_size));

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


ClientState* SettingsState::HandlePackets(GameClient* game) { return &game->settings_state; }


ClientState* SettingsState::HandleInput(GameClient* game) {

    sf::Event settings_event;
    while (game->window.pollEvent(settings_event)) {

        if (settings_event.type == sf::Event::KeyPressed) {

            switch (settings_event.key.code) {

                case sf::Keyboard::Return:
                    return HandleReturn(game);

                case sf::Keyboard::Up:
                    HandleUp(game);
                    return &game->settings_state;

                case sf::Keyboard::Down:
                    HandleDown(game);
                    return &game->settings_state;

                default:
                    return &game->settings_state;

            }

        }

    }

    return &game->settings_state;

}


void SettingsState::Render(GameClient* game) {

    game->window.clear();
    game->window.draw(game->menu_background);
    for (const auto& button : buttons) {
        game->window.draw(button);
    }
    game->window.display();

}


ClientState* SettingsState::HandleReturn(GameClient* game) {

    std::string label = buttons[active_menu].getString();

    if (label == "BACK TO MAIN MENU") {
        return &game->main_menu;
    }
    else {
        return &game->settings_state;
    }

}


void SettingsState::HandleUp(GameClient* game) {

    buttons[active_menu].setFillColor(game->inactive_color);
    active_menu = (active_menu + buttons.size() - 1) % buttons.size();
    buttons[active_menu].setFillColor(game->active_color);

}


void SettingsState::HandleDown(GameClient* game) {

    buttons[active_menu].setFillColor(game->inactive_color);
    active_menu = (active_menu + 1) % buttons.size();
    buttons[active_menu].setFillColor(game->active_color);

}
