#include "CCanvas.h"

CCanvas::CCanvas()
{
	/*m_CanvasImage = nullptr;
	m_CanvTexture = nullptr;*/
	m_RenderWindow = nullptr;
}

CCanvas::CCanvas(sf::RenderWindow* _window, sf::Vector2f _size)
{
	m_RenderWindow = _window;
	m_Size = _size;
	/*m_CanvasImage = new sf::Image();
	m_CanvTexture = new sf::Texture;*/

	m_BGTexture.loadFromFile("Images/Background.jpg");
	m_BackGround.setTexture(m_BGTexture);
	m_BackGround.setOrigin(m_BackGround.getGlobalBounds().width / 2, m_BackGround.getGlobalBounds().height / 2);
	m_BackGround.setScale(_size.x / m_BackGround.getScale().x, _size.y / m_BackGround.getScale().y);
	m_BackGround.setPosition(0.0f, 0.0f);

	m_Canvas = sf::RectangleShape(_size);
	m_Canvas.setOrigin(m_Canvas.getGlobalBounds().width / 2, m_Canvas.getGlobalBounds().height / 2);
	m_Canvas.setPosition(0.0f, 0.0f);
	m_Canvas.setFillColor(sf::Color::White);

	/*m_CanvasImage->create(_size.x, _size.y);
	m_CanvasImage->loadFromFile("Images/Canvas.png");
	m_CanvTexture->loadFromImage(*m_CanvasImage);
	m_Canvas.setTexture(*m_CanvTexture);

	m_Canvas.setOrigin(m_CanvTexture->getSize().x / 2, m_CanvTexture->getSize().y / 2);
	m_Canvas.setPosition(0.0f, 0.0f);*/
}

CCanvas::~CCanvas()
{
	/*m_CanvasImage = nullptr;
	m_CanvTexture = nullptr;
	delete m_CanvasImage;
	delete m_CanvTexture;*/
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
