#pragma once

#include "Protocol.h"
#include <SFML/Network.hpp>

// Class that wraps the sf::UdpSocket and is used to
// send ServerPackets and receive ClientPackets

class ServerSocket {
public:
    // Constructor that binds the given port to the socket
    // Every message has to be sent to this port from clients
    explicit ServerSocket(unsigned short port);

    // Send a ServerPacket to a client
    void Send(ServerPacket& server_packet, const Address& address);

    // Checks and returns if we received anything from the client
    // If we did, we put the received data into client_packet,
    // and the address of the sender into address
    bool Receive(ClientPacket& client_packet, Address& address);

private:
    sf::UdpSocket socket;
};
