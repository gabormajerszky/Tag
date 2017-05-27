#include "ResultState.h"
#include "GameServer.h"


void ResultState::Enter(GameServer* server) {

    std::cout << "Entered RESULT" << std::endl;

    result_timer.restart();

}


ServerState* ResultState::HandlePackets(GameServer* server) {

    // Iterate through the buffer and handle packets
    for (const AddressedPacket& ap : server->buffer) {

        auto player_it = server->player_list.Find(ap.address);
        auto end_it = server->player_list.GetPlayerList().end();

        // The message is from a new player

        if (player_it == end_it) {

            // A player is trying to connect and the game hasn't finished yet
            if (ap.packet.GetMessage() == Message::lobby_input) {
                ServerPacket response(Message::server_full);
                server->socket.Send(response, ap.address);
            }

        }

        // The message is from a connected player

        else {

            if (ap.packet.GetMessage() == Message::disconnect) {
                server->player_list.Remove(ap.address);
            }

            else if (ap.packet.GetMessage() == Message::keep_alive) {
                player_it->ResetAlive();
            }

        }

    }

    server->player_list.KickTimedOut();

    // Check if the result time is over
    if (result_timer.getElapsedTime() > GameConst::RESULT_PERIOD) {
        return &server->lobby;
    }

    return &server->result;

}


void ResultState::Update(PlayerList* player_list) {}


void ResultState::SendUpdates(ServerSocket* socket, const PlayerList& player_list) {

    const std::vector<Player>& players = player_list.GetPlayerList();

    std::vector<std::string> names;
    std::vector<sf::Uint16> scores;

    for (const auto& player : players) {

        names.push_back(player.GetName());
        scores.push_back(player.GetScore());

    }

    // Send updates to every player about the end scores
    assert(players.size() < 128);
    sf::Int8 size = static_cast<sf::Int8>(players.size());

    for (sf::Int8 i = 0; i < size; ++i) {
        ServerPacket packet(names, scores);
        Address address = players[i].GetAddress();
        socket->Send(packet, address);
    }

}
