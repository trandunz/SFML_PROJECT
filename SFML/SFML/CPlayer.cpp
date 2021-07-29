#include <SFML/System/Vector2.hpp>
#include "CPlayer.h"
#include <iostream>

CPlayer::CPlayer()
{
    m_rRenderWindow = nullptr;
    if (m_tTexture.loadFromFile("Images/Player.png"))
    {
        std::cout << "Loaded Player Texture" << std::endl;
    }
    m_sName = "Default";
    m_fHealth = 100.0f;
    m_fAttackDamage = 10.0f;
    m_oBody.setTexture(m_tTexture);
    m_oBody.setOrigin(m_oBody.getGlobalBounds().width / 2, m_oBody.getGlobalBounds().height / 2);
    
    CPlayer::Start();
}

CPlayer::CPlayer(sf::RenderWindow* _renderWindow)
{
    m_rRenderWindow = _renderWindow;
    if (m_tTexture.loadFromFile("Images/Player.png"))
    {
        m_tTexture.setSmooth(true);
        std::cout << "Loaded Player Texture" << std::endl;
    }
	m_sName = "Default";
	m_fHealth = 100.0f;
	m_fAttackDamage = 10.0f;
    m_fMoveSpeed = 3.0f;
    m_oBody.setTexture(m_tTexture);
    m_oBody.setOrigin(m_oBody.getGlobalBounds().width / 2, m_oBody.getGlobalBounds().height / 2);
    m_oBody.setScale(0.5f, 0.5f);
    
    CPlayer::Start();
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
}

void CPlayer::Update()
{
    m_oBody.move(Movement());
    /*LookAtMouse();*/
    m_rRenderWindow->setView(PlayerView());

    
}

void CPlayer::Render()
{
    m_rRenderWindow->draw(m_oBody);
}

sf::Vector2f CPlayer::Movement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_tTexture.loadFromFile("Images/Back.png");
        m_oBody.setTexture(m_tTexture);
        return(sf::Vector2f(0.0f, -m_fMoveSpeed));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //Move Down
    {
        m_tTexture.loadFromFile("Images/Player.png");
        m_oBody.setTexture(m_tTexture);
        return(sf::Vector2f(0.0f, m_fMoveSpeed));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Move Right
    {
        m_tTexture.loadFromFile("Images/SideProfile2.png");
        m_oBody.setTexture(m_tTexture);
        return(sf::Vector2f(m_fMoveSpeed, 0.0f));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Move Left
    {
        m_tTexture.loadFromFile("Images/SideProfile.png");
        m_oBody.setTexture(m_tTexture);
        return(sf::Vector2f(-m_fMoveSpeed, 0));
    }
    else
    {
        m_tTexture.loadFromFile("Images/Player.png");
        m_oBody.setTexture(m_tTexture);
        return(sf::Vector2f(0.0f, 0.0f));
    }
}

void CPlayer::LookAtMouse()
{
    sf::Vector2f curPos = m_oBody.getPosition();
    sf::Vector2i position = sf::Mouse::getPosition((*m_rRenderWindow));

    // now we have both the sprite position and the cursor
    // position lets do the calculation so our sprite will
    // face the position of the mouse
    const float PI = 3.1415926f;

    float dx = curPos.x - position.x;
    float dy = curPos.y - position.y;

    float rotation = (atan2(dy, dx)) * 180 / PI;

    m_oBody.setRotation(rotation + 180);
    //m_oBody.rotate(rotation);
}

sf::View CPlayer::PlayerView()
{
    sf::View PlayerView(m_oBody.getPosition(), sf::Vector2f(500.f, 500.f));
    std::cout << m_oBody.getPosition().x << std::endl;
    std::cout << m_oBody.getPosition().y << std::endl;
    return PlayerView;
}
