#include <SFML/System/Vector2.hpp>
#include "Player.h"

Player::Player(sf::RenderWindow* _renderWindow)
{
	m_rRenderWindow = _renderWindow;
	m_oPlayerBody.setRadius(10.0f);
    Start();
}

Player::~Player()
{
	m_rRenderWindow = nullptr;
}

void Player::Render()
{
	m_rRenderWindow->draw(m_oPlayerBody);
}

void Player::Start()
{
    m_oPlayerBody.setFillColor(sf::Color::White);
    m_oPlayerBody.setOrigin(sf::Vector2f(0.0f, 0.0f));
    redraw = true;
    Update();
}

void Player::Update()
{
    while (m_rRenderWindow->isOpen())
    {
        if (clClock.getElapsedTime().asSeconds() >= 1.0f / m_fFPS)
        {
            redraw = true; //We're ready to redraw everything
            m_oPlayerBody.move(Movement());
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
                m_rRenderWindow->close();
        }

        if (redraw)
        {
            redraw = false;
            m_rRenderWindow->clear();
            m_rRenderWindow->draw(m_oPlayerBody);
            m_rRenderWindow->display();
        }
    }
}

sf::Vector2f Player::Movement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        return(sf::Vector2f(0.0f, 1.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //Move Down
    {
        return(sf::Vector2f(0.0f, -1.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Move Right
    {
        return(sf::Vector2f(1.0f, 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Move Left
    {
        return(sf::Vector2f(-1.0f, 1.0f));
    }
}

sf::View Player::PlayerView()
{
    sf::View PlayerView(m_oPlayerBody.getPosition(), sf::Vector2f(500.f, 500.f));
    m_rRenderWindow->setView(PlayerView);
    return PlayerView;
}
