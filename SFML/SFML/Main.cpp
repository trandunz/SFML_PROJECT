#include "Agent.h"
#include "DebugMenu.h"

static sf::Vector2i WindowSize{ 1000, 1000 };
static float DeltaTime;
static float CurrentTime;
static sf::Clock MainClock{};
static bool ExitProgram;
static std::map<sf::Keyboard::Key, bool> KeyMap;

static sf::RenderWindow* RenderWindow;
static sf::Font m_ArialFont;

void InitWindow(sf::Vector2i&& _size, std::string_view&& _title, sf::Uint32&& _style, sf::ContextSettings&& _settings);
void Start();
void GrabEventInput();
void Update();
void Render();
int Cleanup();

void CalculateDeltaTime();
void HandleEventAction();

sf::ContextSettings RenderWindowSettings;
sf::Event Event;
DebugMenu* DebugControls = nullptr;
std::vector<Agent*> Agents;
std::vector<Obstacle*> Obstacles;

int main()
{
	Start();
	Update();

    return Cleanup();
}

void InitWindow(sf::Vector2i&& _size, std::string_view&& _title, sf::Uint32&& _style, sf::ContextSettings&& _settings)
{
	if (RenderWindow)
	{
		RenderWindow->create(sf::VideoMode(_size.x, _size.y), _title.data(), _style, _settings);
	}
	else
	{
		RenderWindow = new sf::RenderWindow(sf::VideoMode(_size.x, _size.y), _title.data(), _style, _settings);
	}
}

void Start()
{
	RenderWindowSettings.antialiasingLevel = 8;
	InitWindow(std::move(WindowSize), "Steering Behaviors", sf::Style::Default, std::move(RenderWindowSettings));
	RenderWindow->setKeyRepeatEnabled(false);

	m_ArialFont.loadFromFile("Resources/Fonts/ARIAL.TTF");

	// Create Agents
	Agents.emplace_back(new Agent{DeltaTime, WindowSize, RenderWindow, Obstacles, Agents});
	Agents.emplace_back(new Agent{ DeltaTime, WindowSize, RenderWindow, Obstacles, Agents });
	Agents.emplace_back(new Agent{ DeltaTime, WindowSize, RenderWindow, Obstacles, Agents });
	Obstacles.emplace_back(new Obstacle("Resources/Textures/Rock.png", { (float)WindowSize.x /  2,(float)WindowSize.y / 2 }, {0.5f, 0.5f}));
	
	DebugControls = new DebugMenu(Agents, m_ArialFont);
}

void GrabEventInput()
{
	if (RenderWindow->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			ExitProgram = true;

		if (Event.type == sf::Event::KeyPressed)
		{
			KeyMap.insert_or_assign(Event.key.code, true);
		}
		if (Event.type == sf::Event::KeyReleased)
		{
			KeyMap.insert_or_assign(Event.key.code, false);
		}


	}
}

void Update()
{
	//MAIN GAME LOOP
	while (RenderWindow->isOpen())
	{
		CalculateDeltaTime();
		DebugControls->Update();
		GrabEventInput();

		// Object Updates
		HandleEventAction();

		for (auto& obstacle : Obstacles)
		{
			obstacle->Update();
		}

		for (auto& agent : Agents)
		{
			agent->Update();
		}

		//Render
		Render();

		// Check For Program Close
		if (ExitProgram)
		{
			RenderWindow->close();
		}
	}
}
 
void Render()
{
	RenderWindow->clear();

	for (auto& item : Obstacles)
	{
		RenderWindow->draw(*item);
	}

	for (auto& item : Agents)
	{
		RenderWindow->draw(*item);
	}

	RenderWindow->display();

	DebugControls->Render();
}

int Cleanup()
{
	if (DebugControls)
		delete DebugControls;
	DebugControls = nullptr;

	for (auto& agent : Agents)
	{
		if (agent)
			delete agent;
		agent = nullptr;
	}
	Agents.clear();

	for (auto& obstacle : Obstacles)
	{
		if (obstacle)
			delete obstacle;
		obstacle = nullptr;
	}
	Obstacles.clear();

	if (RenderWindow)
		delete RenderWindow;
	RenderWindow = nullptr;

	return EXIT_SUCCESS;
}

void CalculateDeltaTime()
{
	float elapsedTimeSinceProgramStart = MainClock.getElapsedTime().asSeconds();
	DeltaTime = (elapsedTimeSinceProgramStart - CurrentTime);
	CurrentTime = elapsedTimeSinceProgramStart;
}

void HandleEventAction()
{
	for (auto& key : KeyMap)
	{
		if (key.second)
		{
			switch (key.first)
			{
			case sf::Keyboard::Escape:
			{
				ExitProgram = true;

				// Singular Press Please
				key.second = false;
				break;
			}
			default:
				break;
			}
		}
	}

	for (auto& agent : Agents)
	{
		agent->HandleInput();
	}
}
