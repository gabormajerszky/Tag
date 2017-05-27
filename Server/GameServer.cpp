#include "GameServer.h"


void GameServer::Run() {

    // For this gameloop we have to assume the server is fast enough
    // and we'll make sure it's not going to run too fast

    sf::Clock clock;
    sf::Time update_period = sf::seconds(1.0f / static_cast<float>(GameConst::TICK_RATE));
    sf::Time lag;

    // To measure fps

    sf::Clock fps_clock;
    int frame_count = 0;

    // The loop will run indefinitely

    while (true) {

        // Receive packets from clients, and put them into the buffer

        AddressedPacket ap;
        if (socket.Receive(ap.packet, ap.address)) {
            buffer.push_back(ap);
        }

        lag += clock.getElapsedTime();
        clock.restart();

        if (lag > update_period) {

            ServerState* next_state = state->HandlePackets(this);
            if (next_state != state) {
                next_state->Enter(this);
            }
            state = next_state;            
            ClearBuffer();

            state->Update(&player_list);
            state->SendUpdates(&socket, player_list);

            lag -= update_period;

        }

        ++frame_count;

        if (fps_clock.getElapsedTime() > sf::seconds(1.0f)) {
            std::cout << frame_count << " FPS" << std::endl;
            fps_clock.restart();
            frame_count = 0;

        }

    }

}
