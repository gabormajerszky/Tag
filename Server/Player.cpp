#include "Player.h"


void Player::HandleInput(const Input& input) {

    for (InputValue in : input.sequence) {

        switch (in) {

            case InputValue::left:
                velocity.x -= GameConst::PLAYER_VELOCITY;
                break;

            case InputValue::right:
                velocity.x += GameConst::PLAYER_VELOCITY;
                break;

            case InputValue::up:
                velocity.y -= GameConst::PLAYER_VELOCITY;
                break;

            case InputValue::down:
                velocity.y += GameConst::PLAYER_VELOCITY;
                break;

            default:
                break;

        }

    }

}


void Player::Update() {

    position.x += velocity.x;
    position.y += velocity.y;

}


std::ostream& operator << (std::ostream& os, const Player& player) {

    os << "Address: " << player.GetAddress() << std::endl;
    os << "Name: " << player.GetName() << std::endl;
    os << "Color index: " << player.GetColorIndex() << std::endl;
    os << "Position: " << player.GetPosition() << std::endl;
    os << "Velocity: " << player.GetVelocity() << std::endl;
    os << "Score: " << player.GetScore() << std::endl;
    os << "Alive: " << player.GetAliveTime().asSeconds() << " seconds" << std::endl;

    return os;

}
