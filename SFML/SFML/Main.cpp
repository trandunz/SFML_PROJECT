#include "Agent.h"

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

std::vector<Agent*> Agents;

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

	// Create Agents
	Agents.emplace_back(new Agent{});
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
		GrabEventInput();

		// Object Updates
		HandleEventAction();

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

	for (auto& item : Agents)
	{
		RenderWindow->draw(*item);
	}

	RenderWindow->display();
}

int Cleanup()
{
	for (auto& agent : Agents)
	{
		if (agent)
			delete agent;
		agent = nullptr;
	}
	Agents.clear();

	if (RenderWindow)
		delete RenderWindow;
	RenderWindow = nullptr;

	return EXIT_SUCCESS;
}

void CalculateDeltaTime()
{
	float elapsedTimeSinceProgramStart = MainClock.getElapsedTime().asSeconds();
	SetDeltaTime(elapsedTimeSinceProgramStart - CurrentTime);
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
