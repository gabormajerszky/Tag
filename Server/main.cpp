#include <iostream>
#include <string>
#include "GameServer.h"
#include "Test.h"


using namespace std;


#if NDEBUG
const string BUILD = "Release";
#else
const string BUILD = "Debug";
#endif


int main() {

    cout << BUILD << " version started." << endl;

    if (BUILD == "Debug") {
        Test::RunAll();
    }

    GameServer server;
    server.Run();

    return 0;
}
