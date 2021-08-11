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

sf::RenderWindow* m_RenderWindow;

int main()
{
	//WINDOW HANDLE
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);

	//SETTINGS
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

	//OBJECT CREATION
	m_RenderWindow = new sf::RenderWindow(sf::VideoMode(Utils::WINDOWWIDTH, Utils::WINDOWHEIGHT), "SFML works!", sf::Style::Default, settings);
    
    sf::CircleShape circle(100.f); // circle
    sf::RectangleShape square(sf::Vector2f(100, 100)); // square

    circle.setFillColor(sf::Color::Green);
    circle.setPointCount(100);
    square.setPosition(250, 250);
    circle.setPosition(50, 50);

	//
	Start();
	Update();

	// CLEAN UP
	delete m_RenderWindow;
	m_RenderWindow = nullptr;

	//RETURN NULL FOR MAIN
    return 0;
}

void Start() 
{

}

void Update()
{
	//MAIN GAME LOOP
	while (m_RenderWindow->isOpen())
	{
		sf::Event event;
		while (m_RenderWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_RenderWindow->close();
		}
		// Object Updates

		//Render
		Render();
		
	}
}
 
void Render()
{
	m_RenderWindow->clear();

	// Draw Objects
	/*m_RenderWindow->draw(circle);
	m_RenderWindow->draw(square);*/

	m_RenderWindow->display();
}