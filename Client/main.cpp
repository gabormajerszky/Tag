#include <string>
#include "GameClient.h"
#include "Test.h"


using namespace std;


#if NDEBUG
const string BUILD = "Release";
#else
const string BUILD = "Debug";
#endif


int main() {

    if (BUILD == "Debug") {
        Test::RunAll();
    }

    GameClient game;
    game.Run();

    return 0;
}
