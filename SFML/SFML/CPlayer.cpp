#include <SFML/System/Vector2.hpp>
#include "CPlayer.h"
#include <iostream>
#include "CMath.h"

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
    m_fVelocity = sf::Vector2f(0.0f, 0.0f);
    m_oBody.setTexture(m_tTexture);
    m_oBody.setOrigin(m_oBody.getGlobalBounds().width / 2, m_oBody.getGlobalBounds().height / 2);
    
    CPlayer::Start();
}

CPlayer::CPlayer(sf::RenderWindow* _renderWindow)
{
    m_rRenderWindow = _renderWindow;
    m_wWindow = m_rRenderWindow;
    if (m_tTexture.loadFromFile("Images/Player.png"))
    {
        m_tTexture.setSmooth(true);
        std::cout << "Loaded Player Texture" << std::endl;
    }
	m_sName = "Default";
	m_fHealth = 100.0f;
	m_fAttackDamage = 10.0f;
    m_fMoveSpeed = 25.0f + BaseMoveSpeed;
    m_oBody.setTexture(m_tTexture);
    m_oBody.setOrigin(m_oBody.getGlobalBounds().width / 2, m_oBody.getGlobalBounds().height / 2);
    m_oBody.setScale(0.5f, 0.5f);
    m_fVelocity = sf::Vector2f(0.0f, 0.0f);
    
    CPlayer::Start();
}

CPlayer::CPlayer(sf::RenderWindow* _renderWindow, sf::Vector2f _spawnPoint)
{

    m_rRenderWindow = _renderWindow;
    m_wWindow = m_rRenderWindow;
    if (m_tTexture.loadFromFile("Images/Player.png"))
    {
        m_tTexture.setSmooth(true);
        std::cout << "Loaded Player Texture" << std::endl;
    }
    m_sName = "Default";
    m_fHealth = 100.0f;
    m_fAttackDamage = 10.0f;
    m_fMoveSpeed = 25.0f + BaseMoveSpeed;
    m_oBody.setTexture(m_tTexture);
    m_oBody.setOrigin(m_oBody.getGlobalBounds().width / 2, m_oBody.getGlobalBounds().height / 2);
    m_oBody.setScale(0.5f, 0.5f);
    m_oBody.setPosition(_spawnPoint);
    m_fVelocity = sf::Vector2f(0.0f, 0.0f);
    CPlayer::Start();
}

CPlayer::~CPlayer()
{
    m_rRenderWindow = nullptr;
    m_wWindow = nullptr;
}

void CPlayer::Start()
{
    m_CurrentShield = new CItem(CItem::ITEMTYPE::SHIELD);
    m_CurrentShield->m_sSprite.setOrigin(m_CurrentShield->m_sSprite.getGlobalBounds().width / 1, m_CurrentShield->m_sSprite.getGlobalBounds().height / 2);
    m_CurrentShield->m_sSprite.setScale(0.3f, 0.3f);

    m_CurrentItem = new CItem(CItem::ITEMTYPE::SWORD);
    m_CurrentItem->m_sSprite.setOrigin(m_CurrentItem->m_sSprite.getGlobalBounds().width / 0.9, m_CurrentItem->m_sSprite.getGlobalBounds().height / 2);
    m_CurrentItem->m_sSprite.setScale(0.5f, 0.5f);
    m_fCurrentMoveSpeed = m_fMoveSpeed;
}

void CPlayer::Update()
{
    m_CurrentItem->m_sSprite.setPosition(m_oBody.getPosition() + m_fVelocity);
    m_CurrentShield->m_sSprite.setPosition(m_oBody.getPosition() + m_fVelocity);
    LookAtMouse();
    Movement();
    m_oBody.move(m_fVelocity * GetDeltaTime().asSeconds() * m_fCurrentMoveSpeed);
    
    m_rRenderWindow->setView(PlayerView());

    
}

void CPlayer::Render()
{
    if (GetMousePosition().y > 50)
    {
        // moving left
        
        m_rRenderWindow->draw(m_oBody);
        m_CurrentItem->Render(m_rRenderWindow);
        m_CurrentShield->Render(m_rRenderWindow);
    }
    else if (GetMousePosition().y < -50)
    {
        // moving left
        m_CurrentItem->Render(m_rRenderWindow);
        m_CurrentShield->Render(m_rRenderWindow);
        m_rRenderWindow->draw(m_oBody);
    }

    else if (GetMousePosition().x < -50)
    {
        // moving left
        m_CurrentItem->Render(m_rRenderWindow);
        
        m_rRenderWindow->draw(m_oBody);
        m_CurrentShield->Render(m_rRenderWindow);
    }
    else if (GetMousePosition().x > 50)
    {
        // moving left
        
        m_CurrentShield->Render(m_rRenderWindow);
        m_rRenderWindow->draw(m_oBody);
        m_CurrentItem->Render(m_rRenderWindow);
    }
    else
    {
        m_rRenderWindow->draw(m_oBody);
        m_CurrentItem->Render(m_rRenderWindow);
        m_CurrentShield->Render(m_rRenderWindow);
    }
    
}

void CPlayer::CheckCollision(sf::RectangleShape _object)
{
    if (m_oBody.getGlobalBounds().intersects(_object.getGlobalBounds()))
    {
        m_fVelocity.y = 1.0f;
    }
}

void CPlayer::CheckCollision(sf::Sprite _object)
{
    if (m_oBody.getGlobalBounds().intersects(_object.getGlobalBounds()))
    {
        m_fVelocity.y = 1.0f;
    }
}

void CPlayer::Movement()
{
    Position = sf::Vector2f(m_oBody.getPosition().x, m_oBody.getPosition().y);
    m_fVelocity = sf::Vector2f(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        /*m_tTexture.loadFromFile("Images/Back.png");
        m_oBody.setTexture(m_tTexture);*/
        m_fVelocity += sf::Vector2f(0.0f, -1.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //Move Down
    {
        /*m_tTexture.loadFromFile("Images/Player.png");
        m_oBody.setTexture(m_tTexture);*/
        m_fVelocity += (sf::Vector2f(0.0f, 1.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Move Right
    {
        /*m_tTexture.loadFromFile("Images/SideProfile2.png");
        m_oBody.setTexture(m_tTexture);*/
        m_fVelocity += sf::Vector2f(1.0f, 0.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Move Left
    {
        /*m_tTexture.loadFromFile("Images/SideProfile.png");
        m_oBody.setTexture(m_tTexture);*/
        m_fVelocity += sf::Vector2f(-1.0f, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) //Move Left
    {
        m_fCurrentMoveSpeed = 45.0f + BaseMoveSpeed;
    }
    else
    {
        m_fCurrentMoveSpeed = 20.0f + BaseMoveSpeed;
    }

    if (CMath::Magnitude(m_fVelocity) > 1.0f)
    {
        m_fVelocity = CMath::Normalize(m_fVelocity);
    }

    /*if (m_fVelocity == sf::Vector2f(0.0f, 0.0f))
    {
        m_tTexture.loadFromFile("Images/Player.png");
        m_oBody.setTexture(m_tTexture);
    }*/
    /*std::cout << m_fVelocity.x << std::endl;
    std::cout << m_fVelocity.y << std::endl;*/
}

void CPlayer::LookAtMouse()
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*m_wWindow);

    // convert it to world coordinates
    SetMousePosition(m_rRenderWindow->mapPixelToCoords(pixelPos));
    m_vMousePosition -= (m_oBody.getPosition());
    std::cout << GetMousePosition().x << std::endl;
    std::cout << GetMousePosition().y << std::endl;

    if (GetMousePosition().y > 50)
    {
        // moving left
        m_tTexture.loadFromFile("Images/Player.png");
        m_oBody.setTexture(m_tTexture);
        m_CurrentItem->m_tTexture.loadFromFile("Images/SwordFront.png");
        m_CurrentItem->m_sSprite.setTexture(m_CurrentItem->m_tTexture);
        m_CurrentItem->m_sSprite.setOrigin(m_CurrentItem->m_sSprite.getGlobalBounds().width * 1.95f, -m_CurrentItem->m_sSprite.getGlobalBounds().height/3);
        
        m_CurrentShield->m_tTexture.loadFromFile("Images/ShieldFront.png");
        m_CurrentShield->m_sSprite.setTexture(m_CurrentShield->m_tTexture);
        m_CurrentShield->m_sSprite.setOrigin(m_CurrentShield->m_sSprite.getGlobalBounds().width /2, m_CurrentItem->m_sSprite.getGlobalBounds().height * 1.5);

    }
    else if (GetMousePosition().y < -50)
    {
        // moving left
        m_tTexture.loadFromFile("Images/Back.png");
        m_oBody.setTexture(m_tTexture);
        m_CurrentItem->m_tTexture.loadFromFile("Images/SwordBack.png");
        m_CurrentItem->m_sSprite.setTexture(m_CurrentItem->m_tTexture);
        m_CurrentItem->m_sSprite.setOrigin(m_CurrentItem->m_sSprite.getGlobalBounds().width/2, m_CurrentItem->m_sSprite.getGlobalBounds().height);

        m_CurrentShield->m_tTexture.loadFromFile("Images/ShieldFront.png");
        m_CurrentShield->m_sSprite.setTexture(m_CurrentShield->m_tTexture);
        m_CurrentShield->m_sSprite.setOrigin(m_CurrentShield->m_sSprite.getGlobalBounds().width * 2, m_CurrentItem->m_sSprite.getGlobalBounds().height * 1.5);
    }

    else if (GetMousePosition().x < -50)
    {
        // moving left
        m_tTexture.loadFromFile("Images/SideProfile.png");
        m_oBody.setTexture(m_tTexture);
        m_CurrentItem->m_tTexture.loadFromFile("Images/Sword.png");
        m_CurrentItem->m_sSprite.setTexture(m_CurrentItem->m_tTexture);
        m_CurrentItem->m_sSprite.setOrigin(m_CurrentItem->m_sSprite.getGlobalBounds().width * 2, m_CurrentItem->m_sSprite.getGlobalBounds().height / 2);

        m_CurrentShield->m_tTexture.loadFromFile("Images/ShieldLeft.png");
        m_CurrentShield->m_sSprite.setTexture(m_CurrentShield->m_tTexture);
        m_CurrentShield->m_sSprite.setOrigin(m_CurrentShield->m_sSprite.getGlobalBounds().width *3.25f, m_CurrentItem->m_sSprite.getGlobalBounds().height * 1.5);
    }
    else if (GetMousePosition().x > 50)
    {
        // moving left
        m_tTexture.loadFromFile("Images/SideProfile2.png");
        m_oBody.setTexture(m_tTexture);
        m_CurrentItem->m_tTexture.loadFromFile("Images/SwordRight.png");
        m_CurrentItem->m_sSprite.setTexture(m_CurrentItem->m_tTexture);
        m_CurrentItem->m_sSprite.setOrigin(0.0f, m_CurrentItem->m_sSprite.getGlobalBounds().height / 2);

        m_CurrentShield->m_tTexture.loadFromFile("Images/ShieldRight.png");
        m_CurrentShield->m_sSprite.setTexture(m_CurrentShield->m_tTexture);
        m_CurrentShield->m_sSprite.setOrigin(m_CurrentShield->m_sSprite.getGlobalBounds().width /10, m_CurrentItem->m_sSprite.getGlobalBounds().height * 1.5);
    }

    else
    {
        m_tTexture.loadFromFile("Images/Player.png");
        m_oBody.setTexture(m_tTexture);
        m_CurrentItem->m_tTexture.loadFromFile("Images/SwordFront.png");
        m_CurrentItem->m_sSprite.setTexture(m_CurrentItem->m_tTexture);
        m_CurrentItem->m_sSprite.setOrigin(m_CurrentItem->m_sSprite.getGlobalBounds().width * 1.95f, -m_CurrentItem->m_sSprite.getGlobalBounds().height / 3);

        m_CurrentShield->m_tTexture.loadFromFile("Images/ShieldFront.png");
        m_CurrentShield->m_sSprite.setTexture(m_CurrentShield->m_tTexture);
        m_CurrentShield->m_sSprite.setOrigin(m_CurrentShield->m_sSprite.getGlobalBounds().width / 2, m_CurrentItem->m_sSprite.getGlobalBounds().height * 1.5);

    }

    
}

bool CPlayer::HealthCheck()
{
    if (m_fHealth <= 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void CPlayer::SetMousePosition(sf::Vector2f _position)
{
    m_vMousePosition = _position;
}

sf::Vector2f CPlayer::GetMousePosition()
{
    return m_vMousePosition;
}

sf::View CPlayer::PlayerView()
{
    sf::View PlayerView(m_oBody.getPosition(), sf::Vector2f(500.f, 500.f));
    /*std::cout << m_oBody.getPosition().x << std::endl;
    std::cout << m_oBody.getPosition().y << std::endl;*/
    return PlayerView;
}

sf::Sprite CPlayer::GetSprite()
{
    return m_oBody;
}
