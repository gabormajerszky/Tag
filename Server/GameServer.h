#pragma once

#include "LobbyState.h"
#include "MatchState.h"
#include "ResultState.h"

// Main class of the game

class GameServer {

    friend class LobbyState;
    friend class MatchState;
    friend class ResultState;

public:
    // Default constructor
    GameServer() : player_list(GameConst::MAX_PLAYERS),
                   socket(GameConst::PORT),
                   state(&lobby) { state->Enter(this); }

    // Main loop of the game
    void Run();

private:
    // Clears the buffer after the packets have been handled
    void ClearBuffer() { buffer.erase(buffer.begin(), buffer.end()); }
    
    std::vector<AddressedPacket> buffer;
    PlayerList player_list;
    ServerSocket socket;    
    ServerState* state;

    LobbyState lobby;
    MatchState match;
    ResultState result;
};
