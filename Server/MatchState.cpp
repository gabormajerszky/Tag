#include "MatchState.h"
#include "GameServer.h"


float Distance(const sf::Vector2f& pos1, const sf::Vector2f& pos2) {

    double x = static_cast<double>(pos1.x - pos2.x);
    double y = static_cast<double>(pos1.y - pos2.y);

    return static_cast<float>(sqrt(pow(x, 2) + pow(y, 2)));

}


void MatchState::Enter(GameServer* server) {

    std::cout << "Entered MATCH" << std::endl;

    chaser_index = 0;
    last_catch.restart();
    match_timer.restart();

}


ServerState* MatchState::HandlePackets(GameServer* server) {

    // Iterate through the buffer and handle packets
    for (const AddressedPacket& ap : server->buffer) {

        auto player_it = server->player_list.Find(ap.address);
        auto end_it = server->player_list.GetPlayerList().end();

        // The message is from a new player

        if (player_it == end_it) {

            // A player is trying to connect in the middle of a game
            if (ap.packet.GetMessage() == Message::lobby_input) {
                ServerPacket response(Message::server_full);
                server->socket.Send(response, ap.address);
            }

        }

        // The message is from a connected player

        else {

            if (ap.packet.GetMessage() == Message::match_input) {
                player_it->HandleInput(ap.packet.GetInput());
                player_it->ResetAlive();
            }

            else if (ap.packet.GetMessage() == Message::disconnect) {
                server->player_list.Remove(ap.address);
            }

            else if (ap.packet.GetMessage() == Message::keep_alive) {
                player_it->ResetAlive();
            }

        }

    }

    server->player_list.KickTimedOut();

    // Check if we still have enough players to continue the game
    if (server->player_list.Size() < GameConst::MIN_PLAYERS) {
        return &server->lobby;
    }

    // Check if the game is over
    if (match_timer.getElapsedTime() > GameConst::MATCH_PERIOD) {
        return &server->result;
    }

    return &server->match;

}


void MatchState::Update(PlayerList* player_list) {

    player_list->Update();

    // Handle collisions here
    // ...

    // Player's can't yet catch each other
    if (last_catch.getElapsedTime() < GameConst::NO_RECATCH_PERIOD) {
        return;
    }

    auto players = player_list->GetPlayerList();
    sf::Uint8 size = static_cast<sf::Uint8>(players.size());

    for (sf::Uint8 i = 0; i < size; ++i) {
        if (i != chaser_index) {
            sf::Vector2f player1_pos = players[i].GetPosition();
            sf::Vector2f player2_pos = players[chaser_index].GetPosition();
            if (Distance(player1_pos, player2_pos) < 2 * GameConst::PLAYER_RADIUS) {
                chaser_index = i;
                last_catch.restart();
                return;
            }
        }
    }

}


void MatchState::SendUpdates(ServerSocket* socket, const PlayerList& player_list) {

    const std::vector<Player>& players = player_list.GetPlayerList();

    std::vector<std::string> names;
    std::vector<sf::Uint8> color_indexes;
    std::vector<sf::Vector2f> positions;
    std::vector<sf::Vector2f> velocities;
    std::vector<sf::Uint16> scores;

    for (const auto& player : players) {

        names.push_back(player.GetName());
        color_indexes.push_back(player.GetColorIndex());
        positions.push_back(player.GetPosition());
        velocities.push_back(player.GetVelocity());
        scores.push_back(player.GetScore());

    }

    // Send updates to every player with their player index
    assert(players.size() < 128);
    sf::Int8 size = static_cast<sf::Int8>(players.size());

    for (sf::Int8 i = 0; i < size; ++i) {
        ServerPacket packet(
            i, names, color_indexes, chaser_index, positions, velocities, scores
        );
        Address address = players[i].GetAddress();
        socket->Send(packet, address);
    }

}
