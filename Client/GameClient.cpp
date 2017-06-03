#include "GameClient.h"
#include <fstream>


GameClient::GameClient(const sf::VideoMode& vm,
                       const sf::Font& font,
                       const sf::Texture& menu_texture,
                       const sf::Color& active_color,
                       const sf::Color& inactive_color,
                       const Address& address)

    : main_menu(vm, font, active_color, inactive_color),
      settings_state(vm, font, active_color, inactive_color),

      state(&main_menu),
      menu_background(menu_texture),
      active_color(active_color),
      inactive_color(inactive_color),
      socket(address) {

    window.create(vm, "Tag", sf::Style::Fullscreen);
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(false);

}


void GameClient::Run() {

    // Main loop of the game

    sf::Clock timer;
    sf::Time lag;
    sf::Time update_period = sf::seconds(1.0f / GameConst::TICK_RATE);

    sf::Clock fps_timer;
    int frames = 0;

    while (window.isOpen()) {

        state = state->HandlePackets(this);

        lag += timer.getElapsedTime();
        timer.restart();

        if (lag > update_period) {
            lag -= update_period;
            state = state->HandleInput(this);
            ++frames;
        }

        state->Render(this);

        // For debugging
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        // For debugging
        if (fps_timer.getElapsedTime() > sf::seconds(1.0f)) {
            std::cout << frames << std::endl;
            frames = 0;
            fps_timer.restart();
        }

    }

    /*

    std::string name = "Gabor";
    sf::Int8 color_code = 0;
    ClientPacket lobby_packet(name, color_code);
    socket.Send(lobby_packet);

    sf::Texture background_texture;
    background_texture.loadFromFile("res/level background.png");
    sf::Sprite background(background_texture);

    sf::Text fps;
    fps.setFont(font);

    std::vector<sf::CircleShape> players(8);
    for (int i = 0; i < 8; ++i) {
        players[i].setRadius(50);
        players[i].setOrigin(50, 50);
        players[i].setFillColor(sf::Color::Transparent);
    }

    if (local) {
        players[0].setFillColor(sf::Color::Blue);
    }

    sf::Clock timer;
    sf::Clock fps_timer;
    sf::Time lag = timer.getElapsedTime();

    int tick = 0;
    int frames = 0;

    sf::Vector2f velocity(0.0f, 0.0f);

    while (window.isOpen()) {

        ServerPacket server_packet;
        if (socket.Receive(server_packet)) {

            sf::Int8 player_index = server_packet.GetPlayerIndex();

            if (server_packet.GetMessage() == Message::match_update) {
                players[server_packet.GetPlayerIndex()].setFillColor(sf::Color::Red);
                for (size_t i = 0; i < server_packet.GetPositions().size(); ++i) {
                    sf::Vector2f pos = server_packet.GetPositions()[i];
                    if (!local) {
                        players[i].setPosition(pos.x, pos.y);
                    }
                }
            }
        }

        sf::Event myEvent;
        while (window.pollEvent(myEvent)) {
            if (myEvent.type == sf::Event::Closed) {
                window.close();
            }
        }

        lag = timer.getElapsedTime();

        if (lag > sf::microseconds(16667)) {

            lag -= timer.getElapsedTime();
            timer.restart();

            ++tick;

            Input input;
            input.tick = tick;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                input.sequence.push_back(InputValue::left);
                if (local) {
                    velocity.x -= 1;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                input.sequence.push_back(InputValue::right);
                if (local) {
                    velocity.x += 1;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                input.sequence.push_back(InputValue::up);
                if (local) {
                    velocity.y -= 1;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                input.sequence.push_back(InputValue::down);
                if (local) {
                    velocity.y += 1;
                }
            }

            if (input.sequence.size() > 0) {
                ClientPacket input_packet(input);
                socket.Send(input_packet);
            }

            if (local) {
                players[0].move(velocity);
            }

        }

        ++frames;

        if (fps_timer.getElapsedTime() > sf::seconds(1.0f)) {
            fps.setString(std::to_string(frames));
            frames = 0;
            fps_timer.restart();
        }

    }*/

}
