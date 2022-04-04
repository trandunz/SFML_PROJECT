#include <SFML/Graphics.hpp>
#include <Windows.h>

namespace Utils
{
    int WINDOWHEIGHT = 400;
    int WINDOWWIDTH = 400;
}

void Start();
void Update();
void Render();

sf::RenderWindow* RenderWindow;

sf::Event Event;

sf::CircleShape Circle(100.f); // circle
sf::RectangleShape Square(sf::Vector2f(100, 100)); // square

int main()
{
	//WINDOW HANDLE
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);

	//SETTINGS
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

	//OBJECT CREATION
	RenderWindow = new sf::RenderWindow(sf::VideoMode(Utils::WINDOWWIDTH, Utils::WINDOWHEIGHT), "SFML works!", sf::Style::Default, settings);

    Circle.setFillColor(sf::Color::Green);
    Circle.setPointCount(100);
    Square.setPosition(250, 250);
    Circle.setPosition(50, 50);

	//MAIN STUFF
	Start();
	Update();

	//CLEAN UP
	delete RenderWindow;
	RenderWindow = nullptr;

	//RETURN NULL FOR MAIN
    return 0;
}

void Start() 
{

}

void Update()
{
	//MAIN GAME LOOP
	while (RenderWindow->isOpen())
	{
		while (RenderWindow->pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
				RenderWindow->close();
		}
		// Object Updates

		//Render
		Render();
	}
}
 
void Render()
{
	RenderWindow->clear();

	// Draw Objects
	RenderWindow->draw(Circle);
	RenderWindow->draw(Square);

	RenderWindow->display();
}