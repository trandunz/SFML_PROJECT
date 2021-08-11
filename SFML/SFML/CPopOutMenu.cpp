#include "CPopOutMenu.h"

CPopOutMenu::CPopOutMenu(sf::RenderWindow* _RenderWindow)
{
	m_ButtonList[0] = {};
	m_Canvas = nullptr;
	m_Brush = nullptr;
	m_RenderWindow = _RenderWindow;
	m_UIWindow = new sf::RenderWindow(sf::VideoMode(320, 720), "Tools", (sf::Style::Titlebar));
	m_UIWindow->setFramerateLimit((unsigned)120);
}

CPopOutMenu::~CPopOutMenu()
{
	for (int i = 0; i < 1; i++)
	{
		delete m_ButtonList[i];
		m_ButtonList[i] = nullptr;
	}
	delete[] m_ButtonList;
	delete m_UIWindow;
	delete m_Canvas;
	delete m_Brush;
	m_UIWindow = nullptr;
	m_Canvas = nullptr;
	m_Brush = nullptr;
	m_RenderWindow = nullptr;
}

void CPopOutMenu::Start()
{
	m_Canvas = new CCanvas(m_RenderWindow, sf::Vector2f(100.0f, 100.0f));
	m_Brush = new CBrush(m_RenderWindow, m_Canvas);
	m_Brush->m_BushSize = 4;
	m_Brush->m_SideCount = 12;
	m_Brush->m_Rotation = 0.0f;
	m_Brush->m_BrushType = m_Brush->BRUSHTYPE::CUSTOM;

	CButtons* Brush = new CButtons(m_UIWindow);
	Brush->SetLabel("Brush");
	Brush->SetPosition(m_UIWindow->getSize().x / 2, m_UIWindow->getSize().y/2);
	m_ButtonList[0] = Brush;
}

void CPopOutMenu::Update()
{
	sf::Event UIEvent;
	while (m_UIWindow->pollEvent(UIEvent))
	{
		std::cout << m_ButtonList[0]->GetMousePosition().x << std::endl;
		std::cout << m_ButtonList[0]->GetMousePosition().y << std::endl;
		if (UIEvent.type == sf::Event::MouseButtonPressed)
		{
			if (m_ButtonList[0]->bIsinBounds(m_ButtonList[0]->GetMousePosition()))
			{
				m_Brush->m_BrushType = m_Brush->BRUSHTYPE::SQUARE;
			}
		}
		//// Object Updates
		for (int i = 0; i < 1; i++)
		{
			m_ButtonList[i]->Update();
		}
		
		
	}
}

void CPopOutMenu::Render()
{
	m_UIWindow->clear();
	for (int i = 0; i < 1; i++)
	{
		m_ButtonList[i]->Render();
	}
	
	m_UIWindow->display();
}
