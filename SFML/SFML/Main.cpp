#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "CPlayer.h"
#include "CEnemy.h"
#include "CEntity.h"

namespace Utils
{
    int WINDOWHEIGHT = 800;
    int WINDOWWIDTH = 800;
}

float m_fFPS = 60.0f;
sf::Clock clClock;
float DeltaTime;
sf::RenderWindow* m_rRenderWindow;
sf::Window* m_wWindow;
sf::RectangleShape Brush;
CPlayer* pPlayer;
CEnemy* pZombie;
CEnemy* pVampire;
CEnemy* pWereWolf;

bool redraw;

void Update();
void Render();
void Update();

int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_rRenderWindow = new sf::RenderWindow(sf::VideoMode(Utils::WINDOWWIDTH, Utils::WINDOWHEIGHT), "SFML works!", sf::Style::Default, settings);
    Brush = sf::RectangleShape(sf::Vector2f(400, 5));
    clClock = sf::Clock();
    DeltaTime = 0.0f;
    Brush.setFillColor(sf::Color::White);
    Brush.setOrigin(sf::Vector2f(200.0f, 5.0f));
    Brush.setPosition(0.0f, 200.0f);

    pPlayer = new CPlayer(m_rRenderWindow);
    pZombie = new CEnemy(m_rRenderWindow, CEntity::ENTITY_TYPES::ZOMBIE);
    pVampire = new CEnemy(m_rRenderWindow, CEntity::ENTITY_TYPES::VAMPIRE);
    pWereWolf = new CEnemy(m_rRenderWindow, CEntity::ENTITY_TYPES::WEREWOLF);

    pZombie->Movement(sf::Vector2f(100.0f, 100.0f));
    pWereWolf->Movement(sf::Vector2f(-100.0f, 100.0f));
    pVampire->Movement(sf::Vector2f(100.0f, -100.0f));

    Update();

    m_rRenderWindow = nullptr;
    pPlayer = nullptr;
    pZombie = nullptr;
    pVampire = nullptr;
    pWereWolf = nullptr;
    delete m_rRenderWindow;
    delete m_wWindow;
    delete pPlayer;
    delete pZombie;
    delete pVampire;
    delete pWereWolf;

    return (0);
}

void Render()
{
    m_rRenderWindow->draw(Brush);
    m_rRenderWindow->display();
}

void Update()
{
    while (m_rRenderWindow->isOpen())
    {
        pPlayer->Update();
        
        pZombie->Update();
        pZombie->m_vTarget = pPlayer->GetSprite();
        pWereWolf->Update();
        pWereWolf->m_vTarget = pPlayer->GetSprite();
        pVampire->Update();
        pVampire->m_vTarget = pPlayer->GetSprite();
        if (clClock.getElapsedTime().asSeconds() >= 1.0f / m_fFPS)
        {
            redraw = true;
            DeltaTime = clClock.getElapsedTime().asSeconds();
            clClock.restart();
            DeltaTime = 0.0f;
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
            m_rRenderWindow->clear();
            pPlayer->Render();
            pZombie->Render();
            pWereWolf->Render();
            pVampire->Render();
            Render();
        }
    }
    
}