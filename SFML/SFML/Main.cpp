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
//float DeltaTime;
sf::Time DeltaTime;
sf::RenderWindow* m_rRenderWindow;
sf::Window* m_wWindow;
sf::RectangleShape Brush;
CPlayer* pPlayer;
CEnemy* pZombie;
CEnemy* pVampire;
CEnemy* pWereWolf;

sf::Sprite Terrain;

sf::Vector2f TerrainExtents = sf::Vector2f(1000.0f, 1000.0f);

bool redraw;

void Update();
void Render();
void Update();

int main()
{
    //float DeltaTime = 1.0f/ m_fFPS;
    sf::Time DeltaTime;
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::Texture TerrainTexture;
    TerrainTexture.loadFromFile("Images/Grass.png");
    

    Terrain.setTexture(TerrainTexture);


    TerrainTexture.setRepeated(true);
    TerrainTexture.setSmooth(true);
    Terrain.setTextureRect(sf::IntRect(sf::Vector2i(0.0f, 0.0f), (sf::Vector2i)TerrainExtents));
    Terrain.setOrigin(Terrain.getGlobalBounds().width / 2, Terrain.getGlobalBounds().height / 2);
    
    m_rRenderWindow = new sf::RenderWindow(sf::VideoMode(Utils::WINDOWWIDTH, Utils::WINDOWHEIGHT), "SFML works!", sf::Style::Default, settings);
    m_rRenderWindow->setFramerateLimit(60.0f);
    Brush = sf::RectangleShape(sf::Vector2f(1000, 5));
    clClock = sf::Clock();
    Brush.setFillColor(sf::Color::Black);
    Brush.setOrigin(Brush.getGlobalBounds().width / 2, Brush.getGlobalBounds().height / 2);
    Brush.move(0.0f, 200.0f);

    /*sf::RectangleShape Wall2;
    Wall2.setSize(sf::Vector2f(0.0f, 1000.0f));
    Wall2.move(200.0f,0.0f);*/

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
    m_rRenderWindow->draw(Terrain);
    
    pZombie->Render();
    pWereWolf->Render();
    pVampire->Render();
    pPlayer->Render();

    m_rRenderWindow->draw(Brush);

    m_rRenderWindow->display();
}

void Update()
{
    while (m_rRenderWindow->isOpen())
    {
        
        if (clClock.getElapsedTime().asSeconds() >= 1.0f / m_fFPS)
        {
            redraw = true;
           // clClock.restart();
            DeltaTime = clClock.restart();
        }
        else //Sleep until next 1/60th of a second comes around
        {
            sf::Time sleepTime = sf::seconds((1.0f / m_fFPS) - clClock.getElapsedTime().asSeconds());
            sleep(sleepTime);
        }
       
        if (pPlayer->HealthCheck() && pPlayer != nullptr)
        {
            pPlayer->SetDeltaTime(DeltaTime);
            pPlayer->CheckCollision(Brush);
            pPlayer->CheckCollision(pVampire->GetSprite());
            pPlayer->CheckCollision(pZombie->GetSprite());
            pPlayer->CheckCollision(pWereWolf->GetSprite());
            pPlayer->Update();
        }
        else
        {
            delete pPlayer;
        }

        pZombie->SetDeltaTime(DeltaTime);
        pWereWolf->SetDeltaTime(DeltaTime);
        pVampire->SetDeltaTime(DeltaTime);
        

        
        pZombie->Update();
        pWereWolf->Update();
        pVampire->Update();

        

        pVampire->CheckCollision(pPlayer);
        pZombie->CheckCollision(pPlayer);
        pWereWolf->CheckCollision(pPlayer);

        pVampire->CheckCollision(pZombie->GetSprite());
        pZombie->CheckCollision(pVampire->GetSprite());
        pWereWolf->CheckCollision(pZombie->GetSprite());

        pVampire->CheckCollision(pWereWolf->GetSprite());
        pZombie->CheckCollision(pWereWolf->GetSprite());
        pWereWolf->CheckCollision(pVampire->GetSprite());

        pVampire->m_vTarget = pPlayer->GetSprite();
        pZombie->m_vTarget = pPlayer->GetSprite();
        pWereWolf->m_vTarget = pPlayer->GetSprite();

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
            Render();
            
            
        }
    }
    
}