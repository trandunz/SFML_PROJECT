#include "CCanvas.h"

CCanvas::CCanvas()
{
	m_RenderWindow = nullptr;
}

CCanvas::CCanvas(sf::RenderWindow* _window, sf::Vector2f _size)
{
	m_RenderWindow = _window;
	m_BGTexture.loadFromFile("Images/Background.jpg");
	m_BackGround.setTexture(m_BGTexture);
	m_BackGround.setOrigin(m_BackGround.getGlobalBounds().width / 2, m_BackGround.getGlobalBounds().height / 2);
	m_BackGround.setScale(_size.x / m_BackGround.getScale().x, _size.y / m_BackGround.getScale().y);
	m_BackGround.setPosition(0.0f, 0.0f);
	m_Canvas.setSize(_size);
	m_Canvas.setOrigin(m_Canvas.getGlobalBounds().width / 2, m_Canvas.getGlobalBounds().height / 2);
	m_Canvas.setFillColor(sf::Color::White);
	m_Canvas.setPosition(0.0f, 0.0f);
}

CCanvas::~CCanvas()
{
	m_RenderWindow = nullptr;
}

void CCanvas::SetRenderWindow(sf::RenderWindow* _window)
{
	m_RenderWindow = _window;
}

sf::RenderWindow* CCanvas::GetRenderWindow()
{
	return m_RenderWindow;
}

void CCanvas::Start()
{
}

void CCanvas::Update()
{
	/*std::cout << m_Canvas.getPosition().x << std::endl;
	std::cout << m_Canvas.getPosition().y << std::endl;*/
}

void CCanvas::Render()
{
	m_RenderWindow->draw(m_BackGround);
	m_RenderWindow->draw(m_Canvas);
	
}
