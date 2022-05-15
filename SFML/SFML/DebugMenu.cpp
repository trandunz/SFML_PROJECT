// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : DebugMenu.cpp 
// Description : DebugMenu Implementation File
// Author : William Inman
// Mail : william.inman@mds.ac.nz

#include "DebugMenu.h"

DebugMenu::DebugMenu(std::vector<Agent*>& _agents, sf::Font& _globalFont)
{
	// Assign Agents
	m_Agents = &_agents;

	// Assign Pre loaded font
	m_Font = _globalFont;
	Start();
}

DebugMenu::~DebugMenu()
{
	// Cleanup all buttons
	for (auto& button : m_UIButtons)
	{
		if (button)
			delete button;
		button = nullptr;
	}
	m_UIButtons.clear();

	m_Agents = nullptr;

	// Close and cleanup debugMenu renderwindow
	m_RenderWindow->close();
	if (m_RenderWindow)
		delete m_RenderWindow;
	m_RenderWindow = nullptr;
}

void DebugMenu::Start()
{
	// Set debug menu anti-aliasing
	m_ContextSettings.antialiasingLevel = 8;
	// Create the render window with only a title bar and size 300x900
	InitWindow({ 300, 900 }, "Control's", sf::Style::Titlebar, std::move(m_ContextSettings));

	// Insert Debug Line Button and specify on click functionality
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "DebugLines", m_Font, { 300 - 55,  30 }, [this]() {for (auto& agent : *m_Agents) { agent->ToggleDebugLines(); }}));
	// Insert Avoidence Button and specify on click functionality
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Avoidence", m_Font, { 55,  30 }, [this]() {for (auto& agent : *m_Agents) { agent->ToggleAvoidence(); }}));
	// Insert Seek Button and specify on click functionality
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Seek", m_Font, { 55,  80 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('s'); }}));
	// Insert Flee Button and specify on click functionality
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Flee", m_Font, { 55,  130 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('f'); }}));
	// Insert Evade Button and specify on click functionality
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Evade", m_Font, { 55,  180 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('e'); }}));
	// Insert Persuit Button and specify on click functionality
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Persuit", m_Font, { 55,  230 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('p'); }}));
	// Insert Wander Button and specify on click functionality
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Wander", m_Font, { 55,  280 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('w'); }}));
	// Insert Seperation Button and specify on click functionality
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Seperation", m_Font, { 55,  330 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('n'); }}));
	// Insert Alignment Button and specify on click functionality
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Alignment", m_Font, { 55,  380 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('a'); }}));
	// Insert Cohesion Button and specify on click functionality
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Cohesion", m_Font, { 55,  430 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('c'); }}));
	// Insert Flocking Button and specify on click functionality
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Flocking", m_Font, { 55,  480 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('g'); }}));
	// Insert Arrive Button and specify on click functionality
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Arrive", m_Font, { 55,  530 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('r'); }}));
	// Insert Following Button and specify on click functionality
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "L-Following", m_Font, { 55,  580 }, [this]() {for (auto& agent : *m_Agents) {agent->SetState('l'); (*m_Agents)[0]->ToggleLeader();}}));

	// Insert "number of agents" text witth font size 15
	m_UIText.emplace_back(sf::Text("Number Of Agents: ", m_Font, 15));
	// Set its origin to the centre
	SetOriginToCentre(m_UIText.back());
	// Set its position to x:245 y:80
	m_UIText.back().setPosition(245, 80);

}

void DebugMenu::Update()
{
	if (m_RenderWindow->isOpen())
	{
		// Handle button on click registration
		if (m_RenderWindow->pollEvent(m_Event))
		{
			for (auto& button : m_UIButtons)
			{
				button->EventHandler(m_Event);
			}
		}
		// Update all buttons, running on click functionality of clicked
		for (auto& button : m_UIButtons)
		{
			button->Update();
		}

		// Update the agent count
		std::string numberOFEnemies = "Agent Count: ";
		numberOFEnemies += std::to_string(m_Agents->size());
		m_UIText[0].setString(numberOFEnemies);

		// Render The Buttons and text
		Render();
	}
}

void DebugMenu::Render()
{
	m_RenderWindow->clear();
	for (auto& item : m_UIButtons)
	{
		m_RenderWindow->draw(*item);
	}
	for (auto& text : m_UIText)
	{
		m_RenderWindow->draw(text);
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
