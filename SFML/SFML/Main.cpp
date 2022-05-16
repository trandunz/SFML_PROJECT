// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Main.cpp 
// Description : Main Program Implementation File
// Author : William Inman
// Mail : william.inman@mds.ac.nz

#include "DebugMenu.h"

static sf::Vector2i WindowSize{ 1000, 1000 };
static float DeltaTime;
static float CurrentTime;
static sf::Clock MainClock{};
static bool ExitProgram;
static std::map<sf::Keyboard::Key, bool> KeyMap;

static sf::RenderWindow* RenderWindow;
static sf::Font ArialFont;
static sf::Sprite BackgroundSprite;
static sf::Texture BackgroundTexture;

/// <summary>
/// Intializes the RenderWindow.
/// Creates one if non existance or recreates if present.
/// </summary>
/// <param name="_size"></param>
/// <param name="_title"></param>
/// <param name="_style"></param>
/// <param name="_settings"></param>
void InitWindow(sf::Vector2i&& _size, std::string_view&& _title, sf::Uint32&& _style, sf::ContextSettings&& _settings);

/// <summary>
/// Main Start function.
/// Gets called at begining of program
/// </summary>
void Start();

/// <summary>
/// Grabs inputs and stores them in keymap
/// </summary>
void GrabEventInput();

/// <summary>
/// Main Update Function.
/// Gets called every frame
/// </summary>
void Update();

/// <summary>
/// Main draw function.
/// Gets at the end of every frame.
/// </summary>
void Render();

/// <summary>
/// Cleans up all pointers and objects such as renderWindow and agents
/// </summary>
/// <returns></returns>
int Cleanup();

/// <summary>
/// Calculates change in time between frames.
/// Used to scale movement values.
/// </summary>
void CalculateDeltaTime();

/// <summary>
/// Handles event actions.
/// </summary>
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
	// If render window already exists, recreate it else make a new one
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
	// Create window and give it anti-aliasing
	RenderWindowSettings.antialiasingLevel = 8;
	InitWindow(std::move(WindowSize), "Steering Behaviors", sf::Style::Default, std::move(RenderWindowSettings));
	// Make sure no repeating on-press events
	RenderWindow->setKeyRepeatEnabled(false);

	// Load in arial font
	ArialFont.loadFromFile("Resources/Fonts/ARIAL.TTF");

	// Create background water, scale it and repeat it to fit screen
	BackgroundTexture.loadFromFile("Resources/Textures/Water.jpg");
	BackgroundTexture.setRepeated(true);
	BackgroundSprite.setTexture(BackgroundTexture, true);
	BackgroundSprite.setScale(0.5f, 0.5f);
	BackgroundSprite.setTextureRect(sf::IntRect(0.0f, 0.0f, 2 * WindowSize.x, 2 * WindowSize.y));

	// Create An Agent
	Agents.emplace_back(new Agent{ {rand() % WindowSize.x, rand() % WindowSize.y},DeltaTime, WindowSize, RenderWindow, Obstacles, Agents });
	Agents.back()->SetID(Agents.size());

	// Create some obsticles with rock texture
	Obstacles.emplace_back(new Obstacle("Resources/Textures/Rock.png", 
		{ (float)WindowSize.x / 2,(float)WindowSize.y / 2 }, { 0.25f, 0.25f }));
	Obstacles.emplace_back(new Obstacle("Resources/Textures/Rock.png", 
		{ (float)WindowSize.x / 1.27f,(float)WindowSize.y / 1.27f }, { 0.25f, 0.25f }));
	Obstacles.emplace_back(new Obstacle("Resources/Textures/Rock.png", 
		{ (float)WindowSize.x / 1.67f,(float)WindowSize.y / 1.27f }, { 0.25f, 0.25f }));
	Obstacles.emplace_back(new Obstacle("Resources/Textures/Rock.png", 
		{ (float)WindowSize.x / 1.27f,(float)WindowSize.y / 1.67f }, { 0.25f, 0.25f }));
	Obstacles.emplace_back(new Obstacle("Resources/Textures/Rock.png", 
		{ (float)WindowSize.x / 4.27f,(float)WindowSize.y / 4.27f }, { 0.25f, 0.25f }));
	Obstacles.emplace_back(new Obstacle("Resources/Textures/Rock.png", 
		{ (float)WindowSize.x / 2.27f,(float)WindowSize.y / 2.67f }, { 0.25f, 0.25f }));

	// Create debug controls
	DebugControls = new DebugMenu(Agents, ArialFont, DeltaTime, Obstacles, RenderWindow, WindowSize);
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

		if (Event.type == sf::Event::MouseButtonPressed)
		{
			// Spawn agents on mouse whenever group behaviors and or avoidence
			if (Event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(*RenderWindow);
				if (Agents[0]->IsAvoiding())
				{
					auto& agent = Agents.emplace_back(new Agent{ mousePos ,DeltaTime, WindowSize, RenderWindow, Obstacles, Agents});
					agent->SetID(Agents.size());
					agent->SetState(Agents[0]->GetState());
					agent->SetAvoidence(Agents[0]->IsAvoiding());
					agent->SetDebugLines(Agents[0]->IsDebug());
				}
				else if (Agents[0]->GetState() == 'w')
				{
					auto& agent = Agents.emplace_back(new Agent{ mousePos,DeltaTime, WindowSize, RenderWindow, Obstacles, Agents });
					agent->SetID(Agents.size());
					agent->SetState(Agents[0]->GetState());
					agent->SetAvoidence(Agents[0]->IsAvoiding());
					agent->SetDebugLines(Agents[0]->IsDebug());
				}
				else if (Agents[0]->GetState() == 'g')
				{
					auto& agent = Agents.emplace_back(new Agent{ mousePos,DeltaTime, WindowSize, RenderWindow, Obstacles, Agents });
					agent->SetID(Agents.size());
					agent->SetState(Agents[0]->GetState());
					agent->SetAvoidence(Agents[0]->IsAvoiding());
					agent->SetDebugLines(Agents[0]->IsDebug());
				}
				else if (Agents[0]->GetState() == 'l')
				{
					auto& agent = Agents.emplace_back(new Agent{ mousePos,DeltaTime, WindowSize, RenderWindow, Obstacles, Agents });
					agent->SetID(Agents.size());
					agent->SetState(Agents[0]->GetState());
					agent->SetAvoidence(Agents[0]->IsAvoiding());
					agent->SetDebugLines(Agents[0]->IsDebug());
				}
			}
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

		HandleEventAction();

		// Agent updates
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

	sf::RenderStates st;
	st.shader = NULL;

	RenderWindow->draw(BackgroundSprite, st);

	for (auto& item : Obstacles)
	{
		RenderWindow->draw(*item, st);
	}

	for (auto& item : Agents)
	{
		RenderWindow->draw(*item, st);
	}

	RenderWindow->display();

	// Do debugcontrols render
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

	
}
