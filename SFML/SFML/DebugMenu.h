#pragma once
#include "Globals.h"
#include "Button.h"

class DebugMenu
{
public:
	DebugMenu();
	~DebugMenu();

	void Start();
	void Update();
	void Render();

private:
	void InitWindow(sf::Vector2i&& _size, std::string_view&& _title, sf::Uint32&& _style, sf::ContextSettings&& _settings);
	std::vector<Button*> UIButtons;
	sf::Font m_ArialFont;
	sf::Vector2i m_WindowSize;

	sf::Event m_Event;
	sf::RenderWindow* m_RenderWindow = nullptr;
	sf::ContextSettings m_ContextSettings;
};

