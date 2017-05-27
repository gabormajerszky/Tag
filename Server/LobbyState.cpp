#include "LobbyState.h"
#include "GameServer.h"


void LobbyState::Enter(GameServer* server) {

    std::cout << "Entered LOBBY" << std::endl;
    std::cout << "Players: " << server->player_list.Size() << "/"
        << server->player_list.GetMaxPlayers() << std::endl;

}


ServerState* LobbyState::HandlePackets(GameServer* server) {

    // Iterate through the buffer and handle packets
    for (const AddressedPacket& ap : server->buffer) {

        auto player_it = server->player_list.Find(ap.address);
        auto end_it = server->player_list.GetPlayerList().end();

        // The message is from a new player

        if (player_it == end_it) {

            if (ap.packet.GetMessage() == Message::lobby_input) {

                if (!server->player_list.IsFull()) {

                    server->player_list.Add(ap.address);
                    auto new_player = server->player_list.Find(ap.address);
                    new_player->SetName(ap.packet.GetName());
                    new_player->SetColorIndex(ap.packet.GetColorCode());

                }
                else {
                    ServerPacket response(Message::server_full);
                    server->socket.Send(response, ap.address);
                }
                
            }

        }

        // The message is from a connected player

        else {

            if (ap.packet.GetMessage() == Message::lobby_input) {

                player_it->SetName(ap.packet.GetName());
                player_it->SetColorIndex(ap.packet.GetColorCode());
                player_it->ResetAlive();

            }

            else if (ap.packet.GetMessage() == Message::ready) {

                // If there are at least two players,
                // the lobby leader can start the match

                if (server->player_list.Size() >= GameConst::MIN_PLAYERS &&
                    server->player_list.IsLobbyLeader(ap.address)) {
                    return &server->match;
                }                

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
    return &server->lobby;

}


void LobbyState::Update(PlayerList* player_list) {}


void LobbyState::SendUpdates(ServerSocket* socket, const PlayerList& player_list) {

    const std::vector<Player>& players = player_list.GetPlayerList();

    std::vector<std::string> names;
    std::vector<sf::Uint8> color_indexes;

    for (const auto& player : players) {
        names.push_back(player.GetName());
        color_indexes.push_back(player.GetColorIndex());
    }

    assert(players.size() < 128);
    sf::Int8 size = static_cast<sf::Int8>(players.size());

    // Send updates to every player with their player index
    for (sf::Int8 i = 0; i < size; ++i) {
        ServerPacket update(i, names, color_indexes);
        socket->Send(update, players[i].GetAddress());
    }

}
