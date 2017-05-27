#pragma once

#include "Protocol.h"
#include <SFML/System.hpp>


// Class that holds all the information about the player

class Player {
public:
    explicit Player(const Address& address) : address(address) {}
    
    const Address& GetAddress() const { return address; }
    sf::Time GetAliveTime() const { return alive.getElapsedTime(); }

    const std::string& GetName() const { return name; }
    sf::Uint8 GetColorIndex() const { return color_index; }

    const sf::Vector2f& GetPosition() const { return position; }
    const sf::Vector2f& GetVelocity() const { return velocity; }
    sf::Uint16 GetScore() const { return score; }

    void SetName(const std::string& name) { this->name = name; }
    void SetColorIndex(sf::Uint8 color_index) { this->color_index = color_index; }

    // Reset the timer when the player sends a message
    void ResetAlive() { alive.restart(); }

    // Update the player's properties based on the input
    void HandleInput(const Input& input);

    // Update the player's position
    void Update();

private:
    Address address;
    sf::Clock alive;

    std::string name;
    sf::Uint8 color_index = 0;

    sf::Vector2f position = { 0.0f, 0.0f };
    sf::Vector2f velocity = { 0.0f, 0.0f };
    sf::Uint16 score = 0;
};


std::ostream& operator << (std::ostream& os, const Player& player);
