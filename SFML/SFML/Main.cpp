#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Player.h"

namespace Utils
{
    int WINDOWHEIGHT = 400;
    int WINDOWWIDTH = 400;
}


int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(Utils::WINDOWWIDTH, Utils::WINDOWHEIGHT), "SFML works!", sf::Style::Default, settings);
    

    Player pPlayer(window);

    

    return 0;
}