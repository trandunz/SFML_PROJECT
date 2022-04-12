#include "DebugMenu.h"

DebugMenu::DebugMenu()
{
	Start();
}

DebugMenu::~DebugMenu()
{
	for (auto& button : UIButtons)
	{
		if (button)
			delete button;
		button = nullptr;
	}
	UIButtons.clear();

	m_RenderWindow->close();
	if (m_RenderWindow)
		delete m_RenderWindow;
	m_RenderWindow = nullptr;
}

void DebugMenu::Start()
{
	m_ContextSettings.antialiasingLevel = 8;
	InitWindow({ 300, 900 }, "Control's", sf::Style::Titlebar, std::move(m_ContextSettings));

	m_ArialFont.loadFromFile("Resources/Fonts/ARIAL.TTF");
	UIButtons.emplace_back(new Button(m_RenderWindow, "Test", m_ArialFont, { 55,  30 }, []() {std::cout << "Hell Yea" << std::endl; }));

}

void DebugMenu::Update()
{
	if (m_RenderWindow->isOpen())
	{
		if (m_RenderWindow->pollEvent(m_Event))
		{
			for (auto& button : UIButtons)
			{
				button->EventHandler(m_Event);
			}
		}
		for (auto& button : UIButtons)
		{
			button->Update();
		}

		Render();
	}
}

void DebugMenu::Render()
{
	m_RenderWindow->clear();
	for (auto& item : UIButtons)
	{
		m_RenderWindow->draw(*item);
	}
	m_RenderWindow->display();
}

void DebugMenu::InitWindow(sf::Vector2i&& _size, std::string_view&& _title, sf::Uint32&& _style, sf::ContextSettings&& _settings)
{
	m_WindowSize = _size;
	if (m_RenderWindow)
	{
		m_RenderWindow->create(sf::VideoMode(_size.x, _size.y), _title.data(), _style, _settings);
	}
	else
	{
		m_RenderWindow = new sf::RenderWindow(sf::VideoMode(_size.x, _size.y), _title.data(), _style, _settings);
	}
}
