#include <SFML/System/Vector2.hpp>
#include "Player.h"
#include <iostream>

Player::Player(sf::RenderWindow* _renderWindow)
{
	m_rRenderWindow = _renderWindow;
	m_dSpeed = 3.0f;
    Start();
}

Player::Player(sf::RenderWindow* _renderWindow, sf::Vector2f __origin)
{
	m_rRenderWindow = _renderWindow;
	m_dSpeed = 3.0f;
	m_oPlayerBody.setRadius(30.0f);
	m_oPlayerBody.setOrigin(__origin);
	m_oPlayerBody.setPosition(10.0f, 10.0f);
	Start();
}

Player::~Player()
{
	m_rRenderWindow = nullptr;
}

void Player::Start()
{
    m_oPlayerBody.setFillColor(sf::Color::White);
	m_oPlayerBody.setRadius(30.0f);
	m_oPlayerBody.setOrigin(sf::Vector2f(0.0f + m_oPlayerBody.getRadius(), 0.0f + m_oPlayerBody.getRadius()));
	m_oPlayerBody.setPosition(0.0f, 0.0f);

    Update();
}

void Player::Update()
{
    while (m_rRenderWindow->isOpen())
    {
		/*PlayerView();*/
        if (clClock.getElapsedTime().asSeconds() >= 1.0f / m_fFPS)
        {
            redraw = true; //We're ready to redraw everything
            m_oPlayerBody.move(Movement());
			/*PlayerView();*/
            clClock.restart();
        }
        else //Sleep until next 1/60th of a second comes around
        {
            sf::Time sleepTime = sf::seconds((1.0f / m_fFPS) - clClock.getElapsedTime().asSeconds());
            sleep(sleepTime);
        }

        sf::Event event;
        while (m_rRenderWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
				
                m_rRenderWindow->close();
                
            }
                
            
        }

        if (redraw)
        {
            redraw = false;
			m_rRenderWindow->clear(sf::Color::Transparent);
			m_rRenderWindow->draw(m_oPlayerBody);
			std::cout << "Player Drawn" << std::endl;
			m_rRenderWindow->display();
			
        }
    }
}

void Player::Draw()
{
	m_rRenderWindow->draw(m_oPlayerBody);
}

sf::Vector2f Player::Movement()
{
	std::cout << m_oPlayerBody.getPosition().x << std::endl;
	std::cout << m_oPlayerBody.getPosition().y << std::endl;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        return(sf::Vector2f(0.0f, -m_dSpeed));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //Move Down
    {
        return(sf::Vector2f(0.0f, m_dSpeed));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Move Right
    {
        return(sf::Vector2f(m_dSpeed, 0.0f));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Move Left
    {
        return(sf::Vector2f(-m_dSpeed, 0.0f));
    }
    
	return (sf:: Vector2f(0.0f, 0.0f));
}

sf::View Player::PlayerView()
{
    sf::View PlayerView(m_oPlayerBody.getPosition(), sf::Vector2f(1000.f, 1000.f));

    m_rRenderWindow->setView(PlayerView);
    return PlayerView;
}
