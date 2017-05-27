#pragma once

#include "Protocol.h"
#include <SFML/Network.hpp>

// Class that wraps the sf::UdpSocket and is used to
// send ClientPackets and receive ServerPackets

class ClientSocket {
public:
    // The address of the server needs to be provided,
    // since that'll be the only address we can receive messages from
    ClientSocket(const Address& server_address);

    // Send a ClientPacket to the server
    void Send(ClientPacket& client_packet);

    // Checks and returns if we received anything from the server
    // If we did, we put the received data into server_packet
    bool Receive(ServerPacket& server_packet);

private:
    sf::UdpSocket socket;
    Address server_address;
};
