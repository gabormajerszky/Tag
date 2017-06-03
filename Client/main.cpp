#include <string>
#include "GameClient.h"
#include "Test.h"


using namespace std;


#if NDEBUG
const string BUILD = "Release";
#else
const string BUILD = "Debug";
#endif


const int ERROR = 1;


int main() {

    if (BUILD == "Debug") {
        Test::RunAll();
    }

    // We'll use the best available resolution on the computer
    sf::VideoMode vm = sf::VideoMode::getFullscreenModes().front();

    sf::Font font;
    if (!font.loadFromFile("res/captureit.ttf")) {
        std::cerr << "Font file not found or corrupted" << std::endl;
        return ERROR;
    }

    sf::Texture menu_texture;
    if (!menu_texture.loadFromFile("res/menu background.png")) {
        std::cerr << "Menu background not found or corrupted" << std::endl;
        return ERROR;
    }

    Address address;
    if (!address.LoadFromFile("res/ip.txt")) {
        address.SetAddress("0.0.0.0", GameConst::PORT);
    }

    sf::Color active_color = sf::Color::White;
    sf::Color inactive_color = sf::Color(127, 127, 127, 255);

    GameClient game(vm, font, menu_texture, active_color, inactive_color, address);
    game.Run();

    return 0;

}
