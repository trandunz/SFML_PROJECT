// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : DebugMenu.h 
// Description : DebugMenu Header File
// Author : William Inman
// Mail : william.inman@mds.ac.nz

#pragma once
#include "Globals.h"
#include "Button.h"
#include "Agent.h"

class DebugMenu
{
public:
	/// <summary>
	/// Debug Menu Constructor
	/// </summary>
	/// <param name="_agents"></param>
	/// <param name="_globalFont"></param>
	DebugMenu(std::vector<Agent*>& _agents, sf::Font& _globalFont);
		
	/// <summary>
	/// Debug Menu Destructor
	/// </summary>
	~DebugMenu();

	/// <summary>
	/// DebugMenu Start, Gets Called On Contruction
	/// </summary>
	void Start();

	/// <summary>
	/// DebugMenu update, Handles frame-by-frame functionality
	/// </summary>
	void Update();

	/// <summary>
	/// Handles all rendering for the DebugMenu
	/// </summary>
	void Render();

private:
	/// <summary>
	/// Intializes the DebugMenu RenderWindow.
	/// Creates one if non existance or recreates if present.
	/// </summary>
	/// <param name="_size"></param>
	/// <param name="_title"></param>
	/// <param name="_style"></param>
	/// <param name="_settings"></param>
	void InitWindow(sf::Vector2i&& _size, std::string_view&& _title, sf::Uint32&& _style, sf::ContextSettings&& _settings);
	
	std::vector<Button*> m_UIButtons;
	std::vector<sf::Text> m_UIText;
	std::vector<Agent*>* m_Agents;
	sf::Font m_Font;
	sf::Vector2i m_WindowSize;

	sf::Event m_Event;
	sf::RenderWindow* m_RenderWindow = nullptr;
	sf::ContextSettings m_ContextSettings;
};

