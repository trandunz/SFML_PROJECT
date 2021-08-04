#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderWindow* _window, sf::Vector2f _size)
{
	m_RenderWindow = _window;
	m_Canvas.setSize(_size);
	m_Canvas.setOrigin(m_Canvas.getGlobalBounds().width / 2, m_Canvas.getGlobalBounds().height / 2);
	m_Canvas.setFillColor(sf::Color::White);
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
}

void CCanvas::Render()
{
	m_RenderWindow->draw(m_Canvas);
}

void CCanvas::Zoom()
{
	m_Canvas.scale(-1.0f, 1.0f);
}
