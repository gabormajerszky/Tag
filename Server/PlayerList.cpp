#include "PlayerList.h"


bool PlayerList::HasPlayer(const Address& address) const {

    for (const auto& player : players) {
        if (player.GetAddress() == address) {
            return true;
        }
    }

    return false;

}


bool PlayerList::IsLobbyLeader(const Address& address) const {

    if (players.size() == 0) {
        return false;
    }

    if (address == players[0].GetAddress()) {
        return true;
    }
    else {
        return false;
    }

}


std::vector<Player>::iterator PlayerList::Find(const Address& address) {

    for (auto it = players.begin(); it != players.end(); ++it) {
        if (it->GetAddress() == address) {
            return it;
        }
    }

    return players.end();

}


bool PlayerList::Add(const Address& address) {

    if (IsFull()) {
        return false;
    }

    auto it = Find(address);
    if (it == players.end()) {
        players.push_back(Player(address));
        std::cout << "Adding player..." << std::endl;
        std::cout << players.back() << std::endl;
        std::cout << "Players: " << players.size() << "/" << max_players << std::endl;
        return true;
    }
    else {
        return false;
    }

}


void PlayerList::Remove(const Address& address) {

    auto it = Find(address);
    if (it != players.end()) {
        Player removed_player = players.back();
        players.erase(it);
        std::cout << "Removing player..." << std::endl;
        std::cout << removed_player << std::endl;
        std::cout << "Players: " << players.size() << "/" << max_players << std::endl;
    }

}


void PlayerList::KeepAlive(const Address& address) {

    auto it = Find(address);
    if (it != players.end()) {
        it->ResetAlive();
    }

}


void PlayerList::KickTimedOut() {

    // Because we don't want to delete from a vector we're iterating over,
    // this function only kicks the first player we find who timed out
    // This doesn't matter because 99.99% of the time it'll only be one player who times out,
    // and even when not, the other player gets kicked the next tick

    for (const Player& player : players) {
        if (player.GetAliveTime() > GameConst::TIMEOUT_PERIOD) {
            Remove(player.GetAddress());
            return;
        }
    }

}


void PlayerList::Update() {

    for (Player& player : players) {
        player.Update();
    }

}
