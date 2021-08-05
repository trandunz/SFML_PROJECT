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

void CCanvas::ZoomIn()
{
	if (m_Canvas.getScale().x >= 1 && m_Canvas.getScale().y >= 1)
	{
		if (m_Canvas.getGlobalBounds().width > m_RenderWindow->getSize().x || m_Canvas.getGlobalBounds().height > m_RenderWindow->getSize().y)
		{

		}
		else
		{
			m_Canvas.setScale(sf::Vector2f(m_Canvas.getScale().x + 1.0f, m_Canvas.getScale().y + 1.0f));
		}
		
	}

}

void CCanvas::ZoomOut()
{
	if (m_Canvas.getScale().x > 1 && m_Canvas.getScale().y > 1)
	{
		if (m_Canvas.getScale().x > m_RenderWindow->getSize().x || m_Canvas.getScale().y > m_RenderWindow->getSize().y)
		{

		}
		else
		{
			m_Canvas.setScale(sf::Vector2f(m_Canvas.getScale().x - 1.0f, m_Canvas.getScale().y - 1.0f));
		}
		
	}
	
}

