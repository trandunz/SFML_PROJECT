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
	for (int i = 0; i < 5; i++)
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
	CButtons* Square = new CButtons(m_UIWindow);
	CButtons* Circle = new CButtons(m_UIWindow);
	CButtons* Triangle = new CButtons(m_UIWindow);
	CButtons* Custom = new CButtons(m_UIWindow);

	Brush->SetLabel("Brush");
	Square->SetLabel("Square");
	Circle->SetLabel("Circle");
	Triangle->SetLabel("Triangle");
	Custom->SetLabel("Custom");
	Brush->SetPosition(m_UIWindow->getSize().x / 2, m_UIWindow->getSize().y/10);
	Square->SetPosition(m_UIWindow->getSize().x / 2, m_UIWindow->getSize().y / 4);
	Circle->SetPosition(m_UIWindow->getSize().x / 2, m_UIWindow->getSize().y / 2);
	Triangle->SetPosition(m_UIWindow->getSize().x / 2, m_UIWindow->getSize().y / 2 + m_UIWindow->getSize().y / 4);
	Custom->SetPosition(m_UIWindow->getSize().x / 2, m_UIWindow->getSize().y - m_UIWindow->getSize().y / 10);
	m_ButtonList[0] = Brush;
	m_ButtonList[1] = Square;
	m_ButtonList[2] = Circle;
	m_ButtonList[3] = Triangle;
	m_ButtonList[4] = Custom;
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
			if (m_ButtonList[1]->bIsinBounds(m_ButtonList[1]->GetMousePosition()))
			{
				m_Brush->m_BrushType = m_Brush->BRUSHTYPE::SQUARE;
			}
			if (m_ButtonList[2]->bIsinBounds(m_ButtonList[2]->GetMousePosition()))
			{
				m_Brush->m_BrushType = m_Brush->BRUSHTYPE::CIRCLE;
			}
			if (m_ButtonList[3]->bIsinBounds(m_ButtonList[3]->GetMousePosition()))
			{
				m_Brush->m_BrushType = m_Brush->BRUSHTYPE::TRIANGLE;
			}
			if (m_ButtonList[4]->bIsinBounds(m_ButtonList[4]->GetMousePosition()))
			{
				m_Brush->m_BrushType = m_Brush->BRUSHTYPE::CUSTOM;
			}
		}
		//// Object Updates
		for (int i = 0; i < 5; i++)
		{
			m_ButtonList[i]->Update();
		}
		
		
	}
}

void CPopOutMenu::Render()
{
	m_UIWindow->clear();
	for (int i = 0; i < 5; i++)
	{
		m_ButtonList[i]->Render();
	}
	
	m_UIWindow->display();
}
