#include "CButtons.h"

CButtons::CButtons(sf::RenderWindow* _RenderWindow)
{
	m_RenderWindow = _RenderWindow;
	m_IdleTexture.loadFromFile("Images/ButtonIdle.png");
	m_HoverTexture.loadFromFile("Images/ButtonHovering.png");
	m_ClickTexture.loadFromFile("Images/ButtonClick.png");
	m_Font.loadFromFile("Fonts/COMIC.TTF");
	m_tLabel.setFont(m_Font);
	m_tLabel.setCharacterSize(24);
	m_tLabel.setFillColor(sf::Color::Black);
	
	Sprite.setTexture(m_IdleTexture);
	
	/*m_tLabel.setScale(0.5f, 1.0f);
	Sprite.setScale(0.5f, 1.0f);*/
	m_tLabel.setOrigin(sf::Vector2f(m_tLabel.getGlobalBounds().width / 2, m_tLabel.getGlobalBounds().height / 2));
	Sprite.setOrigin(sf::Vector2f(Sprite.getGlobalBounds().width / 2, Sprite.getGlobalBounds().height / 2));
	SetLabel(m_Label);
	
	m_bIsHovering = false;
	m_bIsPressed = false;
	m_bIsClicked = false;
	m_Label = "Default";
	m_OnClickLabel = m_Label;
	m_HoverLabel = m_Label;

	if (m_tLabel.getGlobalBounds().height <= 18)
	{ 
		m_Adjustment = 0;
	}
	else if (m_tLabel.getGlobalBounds().height >= 23)
	{ 
		m_Adjustment = 5;
	}
}

CButtons::~CButtons()
{
	delete m_RenderWindow;
	m_RenderWindow = nullptr;
}

void CButtons::Start()
{
}

void CButtons::Update()
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((*m_RenderWindow));
	SetMousePosition(m_RenderWindow->mapPixelToCoords(pixelPos));
	bIsinBounds(m_vMousePosition);
}

void CButtons::Render()
{
	m_RenderWindow->draw(Sprite);
	m_RenderWindow->draw(m_tLabel);
}

void CButtons::SetMousePosition(sf::Vector2f Position)
{
	m_vMousePosition = Position;
}

sf::Vector2f CButtons::GetMousePosition()
{
	/*std::cout << m_vMousePosition.x << std::endl;
	std::cout << m_vMousePosition.y << std::endl;*/

	return m_vMousePosition;
}

void CButtons::SetPosition(float newX, float newY)
{
	/*X = newX;
	Y = newY;
	X2 = newX + Sprite.getGlobalBounds().width;
	Y2 = newY + Sprite.getGlobalBounds().height;*/
	Sprite.setPosition(sf::Vector2f(newX, newY));
	m_tLabel.setPosition(sf::Vector2f(newX, newY));
}

void CButtons::SetLabel(string x)
{
	string oldLabel = m_Label;
	string oldClickLabel = m_OnClickLabel;
	if (x != m_OnClickLabel && x != m_HoverLabel) {
		m_Label = x;
	}
	if (m_OnClickLabel == oldLabel && x != m_HoverLabel) {
		m_OnClickLabel = x;
	}
	if (m_HoverLabel == oldLabel && x != oldClickLabel) {
		m_HoverLabel = x;
	}
	m_tLabel.setString(x);
	if (m_tLabel.getGlobalBounds().height <= 18) { m_Adjustment = 0; }
	if (m_tLabel.getGlobalBounds().height >= 23) { m_Adjustment = 5; }
	m_tLabel.setOrigin(sf::Vector2f(m_tLabel.getGlobalBounds().width / 2, m_tLabel.getGlobalBounds().height / 2));
}

void CButtons::SetState(string type)
{
	if (type == "Idle") {
		Sprite.setTexture(m_IdleTexture);
	}
	else if (type == "Hover") {
		Sprite.setTexture(m_HoverTexture);
	}
	else if (type == "Click") {
		Sprite.setTexture(m_ClickTexture);
	}
}

bool CButtons::bIsinBounds(sf::Vector2f _vMousePosition)
{
	if (Sprite.getGlobalBounds().contains(sf::Vector2f(_vMousePosition.x, _vMousePosition.y)))
	{
		if (m_bIsPressed != true) {
			Sprite.setTexture(m_HoverTexture);
			SetLabel(m_HoverLabel);
			SetState("Hover");
		}
		m_bIsHovering = true;
		/*std::cout << "MousedOverButton" << std::endl;*/
		return true;
	}
	else
	{
		if (m_bIsPressed != true) {
			Sprite.setTexture(m_IdleTexture);
			SetLabel(m_Label);
		}
		SetState("Idle");
		m_bIsHovering = false;
		return false;
	}
}

int CButtons::GetHeight()
{
	return Sprite.getGlobalBounds().height;
}

int CButtons::GetWidth()
{
	return Sprite.getGlobalBounds().width;
}