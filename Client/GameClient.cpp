#include "GameClient.h"
#include "ClientSocket.h"
#include <SFML\Graphics.hpp>


void GameClient::Run() {

    // Main loop of the game

    // !!! THROWAWAY CODE !!!

    bool local = true;

    std::string server_ip = "163.172.180.245";

    Address address("192.168.0.23", 50000);
    ClientSocket socket(address);

    std::string name = "Gabor";
    sf::Int8 color_code = 0;
    ClientPacket lobby_packet(name, color_code);
    socket.Send(lobby_packet);

    sf::Texture background_texture;
    background_texture.loadFromFile("res/level background.png");
    sf::Sprite background(background_texture);

    sf::Font font;
    font.loadFromFile("res/captureit.ttf");
    sf::Text play("PLAY", font, 60);
    play.setPosition(960, 540);

    sf::Text fps;
    fps.setFont(font);

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Window", sf::Style::Fullscreen);
    window.setKeyRepeatEnabled(false);

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

        window.clear();
        window.draw(background);
        window.draw(play);
        for (size_t i = 0; i < players.size(); ++i) {
            window.draw(players[i]);
        }
        window.draw(fps);
        window.display();

        ++frames;

        if (fps_timer.getElapsedTime() > sf::seconds(1.0f)) {
            fps.setString(std::to_string(frames));
            frames = 0;
            fps_timer.restart();
        }

    }

}
