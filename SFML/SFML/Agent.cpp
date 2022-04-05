#include "Agent.h"

Agent::Agent()
{
	Start();
}

Agent::~Agent()
{
}

void Agent::Start()
{
	m_SpriteTexture.loadFromFile("Resources/Textures/SpaceShip.png");

	m_Sprite.setTexture(m_SpriteTexture, true);
	m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2, m_Sprite.getGlobalBounds().height / 2);
	m_Sprite.setPosition((float)WindowSize.x / 2, (float)WindowSize.y / 2);
	m_Sprite.setScale({ 0.2f, 0.2f });
}

void Agent::Update()
{
	Print(std::move(DeltaTime));
	Translate({ 0, m_MaxSpeed * DeltaTime });
}

void Agent::HandleInput()
{
	/*for (auto& key : KeyMap)
	{
		if (key.second)
		{
			switch (key.first)
			{
			default:
				break;
			}
		}
	}*/
}

void Agent::Translate(sf::Vector2f&& _translation)
{
	m_Sprite.setPosition(m_Sprite.getPosition().x + _translation.x, m_Sprite.getPosition().y + _translation.y);
}

void Agent::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Sprite, _states);
}
