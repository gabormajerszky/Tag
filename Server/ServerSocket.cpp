#include "ServerSocket.h"
#include <cassert>


ServerSocket::ServerSocket(unsigned short port) {

    // Make sure sockets aren't blocking
    socket.setBlocking(false);
    sf::Socket::Status status = socket.bind(port);

    // For now, we'll just assert the port isn't being used.
    // If it causes problems a more robust error handling is required.
    assert(status == sf::Socket::Done);

}


void ServerSocket::Send(ServerPacket& server_packet, const Address& address) {

    sf::Packet packet;
    packet << server_packet;
    socket.send(packet, address.GetIp(), address.GetPort());

}


bool ServerSocket::Receive(ClientPacket& client_packet, Address& address) {

    sf::Packet packet;
    sf::IpAddress remote_address;
    unsigned short remote_port;

    sf::Socket::Status status = socket.receive(packet, remote_address, remote_port);

    // Check if we received data
    if (status == sf::Socket::Done) {
        packet >> client_packet;
        address.SetAddress(remote_address, remote_port);
        return true;
    }
    else {
        return false;
    }

}
