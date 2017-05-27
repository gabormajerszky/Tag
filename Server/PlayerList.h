#pragma once

#include "Player.h"

// This class handles adding and removing players

class PlayerList {
public:
    explicit PlayerList(unsigned int max_players) : max_players(max_players) {}

    // Return if the players list is full
    bool IsFull() const { return players.size() == max_players; }

    // Return if the players list is empty
    bool IsEmpty() const { return players.size() == 0; }

    // Return the size of the current playerlist
    size_t Size() const { return players.size(); }

    // Return the maximum allowed players
    size_t GetMaxPlayers() const { return max_players; }

    const std::vector<Player>& GetPlayerList() const { return players; }

    // Return whether or not the player with the given address is in the list
    bool HasPlayer(const Address& address) const;

    // Return whether the player is the lobby leader
    bool IsLobbyLeader(const Address& address) const;

    // Returns an iterator to the player with the given address,
    // if player not found, an iterator to the end is returned
    std::vector<Player>::iterator Find(const Address& address);

    // Add a player and also return whether the operation was successful
    bool Add(const Address& address);

    // Remove a player if they are in the list
    void Remove(const Address& address);

    // Remove every player from the list
    void RemoveAll() { players.clear(); }

    // Reset the player's clock if they are in the list
    void KeepAlive(const Address& address);

    // Kick players who hasn't sent any message for a while
    void KickTimedOut();

    // Update every player individually
    void Update();

private:
    std::vector<Player> players;
    const unsigned int max_players;
};

