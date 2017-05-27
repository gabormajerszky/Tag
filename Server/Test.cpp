#include "Test.h"
#include "PlayerList.h"
#include <chrono>
#include <thread>


void Test::ServerPacketTest() {

    int count = static_cast<int>(Message::count);
    for (int i = 0; i < count; ++i) {

        Message message = static_cast<Message>(i);

        if (message != Message::none &&
            message != Message::lobby_input &&
            message != Message::match_input &&
            message != Message::count) {

            sf::Packet packet;

            {

                sf::Int8 player_index = 1;
                std::vector<std::string> names = { "John", "Joe", "Jeff" };
                std::vector<sf::Uint8> color_indexes = { 3, 5, 7 };
                std::vector<sf::Uint16> scores = { 100, 200, 300 };


                if (message == Message::lobby_update) {

                    ServerPacket sent(player_index, names, color_indexes);
                    packet << sent;

                }

                else if (message == Message::match_update) {

                    sf::Int8 chaser_index = 2;
                    std::vector<sf::Vector2f> positions = {
                        { 1.1f, 2.2f },{ 3.3f, 4.4f },{ 5.5f, 6.6f }
                    };
                    std::vector<sf::Vector2f> velocities = {
                        { 1.1f, 2.2f },{ 3.3f, 4.4f },{ 5.5f, 6.6f }
                    };
                    

                    ServerPacket sent(player_index, names, color_indexes,
                        chaser_index, positions, velocities, scores);
                    packet << sent;

                }

                else if (message == Message::result_update) {

                    ServerPacket sent(names, scores);
                    packet << sent;

                }

                else {

                    ServerPacket sent(message);
                    packet << sent;

                }

            }

            ServerPacket received;
            packet >> received;
            
            if (received.GetMessage() != message) {
                std::cout << "ServerPacketTest failed: mismatching messages" << std::endl;
                std::cout << "Sent: " << message << std::endl;
                std::cout << "Received: " << received.GetMessage() << std::endl;
                return;
            }

            if (received.GetMessage() == Message::lobby_update ||
                received.GetMessage() == Message::match_update) {

                if (received.GetPlayerIndex() != 1) {
                    std::cout << "ServerPacketTest failed: mismatching player indexes" << std::endl;
                    return;
                }

                if (received.GetNames().size() != 3) {
                    std::cout << "ServerPacketTest failed: mismatching name vector size" << std::endl;
                    return;
                }

                if (received.GetNames()[0] != "John" ||
                    received.GetNames()[1] != "Joe" ||
                    received.GetNames()[2] != "Jeff") {
                    std::cout << "ServerPacketTest failed: mismatching names" << std::endl;
                    return;
                }

                if (received.GetColorIndexes().size() != 3) {
                    std::cout << "ServerPacketTest failed: mismatching color vector size" << std::endl;
                    return;
                }

                if (received.GetColorIndexes()[0] != 3 ||
                    received.GetColorIndexes()[1] != 5 ||
                    received.GetColorIndexes()[2] != 7) {
                    std::cout << "ServerPacketTest failed: mismatching colors" << std::endl;
                    return;
                }

            }

            if (received.GetMessage() == Message::match_update) {

                if (received.GetChaserIndex() != 2) {
                    std::cout << "ServerPacketTest failed: mismatching chaser index" << std::endl;
                    return;
                }

                if (received.GetPositions().size() != 3) {
                    std::cout << "ServerPacketTest failed: mismatching position vector size" << std::endl;
                    return;
                }

                if (received.GetPositions()[0] != sf::Vector2f(1.1f, 2.2f) ||
                    received.GetPositions()[1] != sf::Vector2f(3.3f, 4.4f) ||
                    received.GetPositions()[2] != sf::Vector2f(5.5f, 6.6f)) {
                    std::cout << "ServerPacketTest failed: mismatching positions" << std::endl;
                    return;
                }

                if (received.GetVelocities().size() != 3) {
                    std::cout << "ServerPacketTest failed: mismatching velocity vector size" << std::endl;
                    return;
                }

                if (received.GetPositions()[0] != sf::Vector2f(1.1f, 2.2f) ||
                    received.GetPositions()[1] != sf::Vector2f(3.3f, 4.4f) ||
                    received.GetPositions()[2] != sf::Vector2f(5.5f, 6.6f)) {
                    std::cout << "ServerPacketTest failed: mismatching velocities" << std::endl;
                    return;
                }

                if (received.GetScores().size() != 3) {
                    std::cout << "ServerPacketTest failed: mismatching score vector size" << std::endl;
                    return;
                }

                if (received.GetScores()[0] != 100 ||
                    received.GetScores()[1] != 200 ||
                    received.GetScores()[2] != 300) {
                    std::cout << "ServerPacketTest failed: mismatching scores" << std::endl;
                    return;
                }

            }

            if (received.GetMessage() == Message::lobby_update) {

                if (received.GetNames()[0] != "John" ||
                    received.GetNames()[1] != "Joe" ||
                    received.GetNames()[2] != "Jeff") {
                    std::cout << "ServerPacketTest failed: mismatching names" << std::endl;
                    return;
                }

            }

        }

    }

    std::cout << "ServerPacketTest passed" << std::endl;

}


void Test::ClientPacketTest() {

    int count = static_cast<int>(Message::count);

    for (int i = 0; i < count; ++i) {

        Message message = static_cast<Message>(i);

        if (message != Message::none &&
            message != Message::lobby_update &&
            message != Message::match_update &&
            message != Message::count) {

            sf::Packet packet;

            {

                if (message == Message::lobby_input) {

                    ClientPacket sent("Gabor", 3);
                    packet << sent;

                }


                else if (message == Message::match_input) {

                    Input input;
                    input.tick = 42;

                    input.sequence.push_back(InputValue::left);
                    input.sequence.push_back(InputValue::up);
                    input.sequence.push_back(InputValue::right);

                    ClientPacket sent(input);
                    packet << sent;

                }

                else {

                    ClientPacket sent(message);
                    packet << sent;

                }
            }

            ClientPacket received;
            packet >> received;

            Message message = static_cast<Message>(i);

            if (received.GetMessage() != message) {
                std::cout << "ClientPacketTest failed: mismatching messages" << std::endl;
                return;
            }

            if (received.GetMessage() == Message::lobby_input) {

                if (received.GetName() != "Gabor") {
                    std::cout << "ClientPacketTest failed: mismatching names" << std::endl;
                }
                if (received.GetColorCode() != 3) {
                    std::cout << "ClientPacketTest failed: mismatching colors" << std::endl;
                }

            }

            if (received.GetMessage() == Message::match_input) {

                if (received.GetInput().tick != 42) {
                    std::cout << "ClientPacketTest failed: mismatching IDs" << std::endl;
                    return;
                }

                if (received.GetInput().sequence.size() != 3) {
                    std::cout << "ClientPacketTest failed: wrong input size" << std::endl;
                }

                if (received.GetInput().sequence[0] != InputValue::left ||
                    received.GetInput().sequence[1] != InputValue::up ||
                    received.GetInput().sequence[2] != InputValue::right) {
                    std::cout << "ClientPacketTest failed: mismatching inputs" << std::endl;
                    return;
                }

            }

            else {

                if (received.GetInput().sequence.size() > 0) {
                    std::cout << "ClientPacketTest failed: unexpected input data" << std::endl;
                    return;
                }

            }

        }

    }

    std::cout << "ClientPacketTest passed" << std::endl;

}


void Test::PlayerTest() {

    Address address("192.168.0.1", 1);
    Player player(address);

    if (player.GetAddress() != address) {
        std::cout << "PlayerTest failed: mismatching address" << std::endl;
        return;
    }

    if (player.GetPosition() != sf::Vector2f(0.0f, 0.0f)) {
        std::cout << "PlayerTest failed: mismatching positions" << std::endl;
        return;
    }

    sf::Int32 alive_time = player.GetAliveTime().asMilliseconds();

    if (alive_time > 10) {
        std::cout << "PlayerTest failed: unexpected player timer - "
            << alive_time << "ms" << std::endl;
        return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    alive_time = player.GetAliveTime().asMilliseconds();

    if (alive_time < 90 || alive_time > 110) {
        std::cout << "PlayerTest failed: unexpected player timer - "
            << alive_time << "ms" << std::endl;
        return;
    }

    player.ResetAlive();
    alive_time = player.GetAliveTime().asMilliseconds();

    if (alive_time > 10) {
        std::cout << "PlayerTest failed: unexpected player timer - "
            << alive_time << "ms" << std::endl;
        return;
    }

    std::cout << "PlayerTest passed" << std::endl;

}


void Test::PlayerListTest() {

    Address address1("192.168.0.1", 1);
    Address address2("192.168.0.1", 2);
    Address address3("192.168.0.1", 3);
    Address address4("192.168.0.1", 4);
    Address address5("192.168.0.1", 5);

    PlayerList player_list(4);

    if (!player_list.IsEmpty()) {
        std::cout << "PlayerListTest failed: unexpected player" << std::endl;
        return;
    }

    player_list.Remove(address1);

    if (!player_list.IsEmpty()) {
        std::cout << "PlayerListTest failed: unexpected player" << std::endl;
        return;
    }

    if (player_list.Add(address1) != true) {
        std::cout << "PlayerListTest failed: unexpected message" << std::endl;
        return;
    }

    if (player_list.Add(address1) != false) {
        std::cout << "PlayerListTest failed: unexpected message" << std::endl;
        return;
    }

    if (player_list.Add(address2) != true) {
        std::cout << "PlayerListTest failed: unexpected message" << std::endl;
        return;
    }

    if (player_list.Add(address3) != true) {
        std::cout << "PlayerListTest failed: unexpected message" << std::endl;
        return;
    }

    if (player_list.Add(address4) != true) {
        std::cout << "PlayerListTest failed: unexpected message" << std::endl;
        return;
    }

    if (!player_list.IsFull()) {
        std::cout << "PlayerListTest failed: missing player" << std::endl;
        return;
    }

    if (player_list.Add(address5) != false) {
        std::cout << "PlayerListTest failed: added player when full" << std::endl;
        return;
    }

    player_list.Remove(address5);

    if (!player_list.IsFull()) {
        std::cout << "PlayerListTest failed: wrong player removed" << std::endl;
        return;
    }

    player_list.Remove(address3);

    if (player_list.IsFull()) {
        std::cout << "PlayerListTest failed: player was not removed" << std::endl;
        return;
    }

    if (player_list.Add(address5) != true) {
        std::cout << "PlayerListTest failed: unable to add player" << std::endl;
        return;
    }

    if (!player_list.IsFull()) {
        std::cout << "PlayerListTest failed: missing player" << std::endl;
        return;
    }

    std::cout << "PlayerListTest passed" << std::endl;

}


void Test::RunAll() {

    ServerPacketTest();
    ClientPacketTest();
    PlayerTest();
    PlayerListTest();

}
