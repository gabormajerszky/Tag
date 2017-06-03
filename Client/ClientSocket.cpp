#include "ClientSocket.h"
#include <cassert>


ClientSocket::ClientSocket() {

    socket.setBlocking(false);
    sf::Socket::Status status = socket.bind(sf::Socket::AnyPort);

    // We'll assume we were able to find a free port
    assert(status == sf::Socket::Done);
}


ClientSocket::ClientSocket(const Address& server_address)
    : server_address(server_address) {

    socket.setBlocking(false);
    sf::Socket::Status status = socket.bind(sf::Socket::AnyPort);

    // We'll assume we were able to find a free port
    assert(status == sf::Socket::Done);

}


void ClientSocket::SetAddress(const Address& server_address) {

    this->server_address = server_address;

}


void ClientSocket::Send(ClientPacket& client_packet) {

    sf::Packet packet;
    packet << client_packet;
    socket.send(packet, server_address.GetIp(), server_address.GetPort());

}


bool ClientSocket::Receive(ServerPacket& server_packet) {

    sf::Packet packet;
    sf::IpAddress remote_address;
    unsigned short remote_port;

    sf::Socket::Status status = socket.receive(packet, remote_address, remote_port);

    // Check if we received data AND if it's from the server
    if (status == sf::Socket::Done &&
        server_address.GetIp() == remote_address &&
        server_address.GetPort() == remote_port) {

        packet >> server_packet;
        return true;

    }
    // We either didn't receive a message,
    // or it wasn't from the server so we'll ignore it
    else {
        return false;
    }

}
