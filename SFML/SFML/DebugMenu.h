#pragma once
#include "Globals.h"
#include "Button.h"
#include "Agent.h"

class DebugMenu
{
public:
	DebugMenu(std::vector<Agent*>& _agents, sf::Font& _globalFont);
	~DebugMenu();

	void Start();
	void Update();
	void Render();

private:
	void InitWindow(sf::Vector2i&& _size, std::string_view&& _title, sf::Uint32&& _style, sf::ContextSettings&& _settings);
	std::vector<Button*> m_UIButtons;
	std::vector<Agent*>* m_Agents;
	sf::Font m_Font;
	sf::Vector2i m_WindowSize;

	sf::Event m_Event;
	sf::RenderWindow* m_RenderWindow = nullptr;
	sf::ContextSettings m_ContextSettings;
};

