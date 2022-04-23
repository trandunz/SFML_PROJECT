#include "DebugMenu.h"

DebugMenu::DebugMenu(std::vector<Agent*>& _agents, sf::Font& _globalFont)
{
	m_Agents = &_agents;
	m_Font = _globalFont;
	Start();
}

DebugMenu::~DebugMenu()
{
	for (auto& button : m_UIButtons)
	{
		if (button)
			delete button;
		button = nullptr;
	}
	m_UIButtons.clear();

	m_Agents = nullptr;

	m_RenderWindow->close();
	if (m_RenderWindow)
		delete m_RenderWindow;
	m_RenderWindow = nullptr;
}

void DebugMenu::Start()
{
	m_ContextSettings.antialiasingLevel = 8;
	InitWindow({ 300, 900 }, "Control's", sf::Style::Titlebar, std::move(m_ContextSettings));

	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Avoidence", m_Font, { 55,  30 }, [this]() {for (auto& agent : *m_Agents) { agent->ToggleAvoidence(); }}));
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Seek", m_Font, { 55,  80 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('s'); }}));
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Flee", m_Font, { 55,  130 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('f'); }}));
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Evade", m_Font, { 55,  180 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('e'); }}));
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Persuit", m_Font, { 55,  230 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('p'); }}));
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Wander", m_Font, { 55,  280 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('w'); }}));
	m_UIButtons.emplace_back(new Button(m_RenderWindow, "Seperation", m_Font, { 55,  330 }, [this]() {for (auto& agent : *m_Agents) { agent->SetState('n'); }}));
}

void DebugMenu::Update()
{
	if (m_RenderWindow->isOpen())
	{
		if (m_RenderWindow->pollEvent(m_Event))
		{
			for (auto& button : m_UIButtons)
			{
				button->EventHandler(m_Event);
			}
		}
		for (auto& button : m_UIButtons)
		{
			button->Update();
		}

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
