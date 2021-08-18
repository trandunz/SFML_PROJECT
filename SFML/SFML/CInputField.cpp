#include "CInputField.h"

CInputField::CInputField(sf::RenderWindow* _RenderWindow)
{
    m_RenderWindow = _RenderWindow;
    m_IdleTexture.loadFromFile("Images/ButtonHovering.png");
    m_HoverTexture.loadFromFile("Images/ButtonHovering.png");
    m_Font.loadFromFile("Fonts/times.TTF");
    m_tLabel.setFont(m_Font);
    m_tLabel.setCharacterSize(24);
    m_tLabel.setFillColor(sf::Color::Black);
    Sprite.setTexture(m_IdleTexture);
    m_tLabel.setOrigin(sf::Vector2f(m_tLabel.getGlobalBounds().width / 2, m_tLabel.getGlobalBounds().height / 2));
    Sprite.setOrigin(sf::Vector2f(Sprite.getGlobalBounds().width / 2, Sprite.getGlobalBounds().height / 2));
    m_Label = "Input Value";
    SetLabel(m_Label);
    m_bIsHovering = false;
    m_bIsPressed = false;
    m_OnClickLabel = m_Label;
    m_HoverLabel = m_Label;
}

CInputField::~CInputField()
{
    m_RenderWindow = nullptr;
}

void CInputField::Update()
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition((*m_RenderWindow));
    SetMousePosition(m_RenderWindow->mapPixelToCoords(pixelPos));
    bIsinBounds(m_vMousePosition);


}

void CInputField::Render()
{
    m_RenderWindow->draw(Sprite);
    m_RenderWindow->draw(m_tLabel);
}

void CInputField::SetMousePosition(sf::Vector2f Position)
{
    m_vMousePosition = Position;
}

sf::Vector2f CInputField::GetMousePosition()
{
    return m_vMousePosition;
}

bool CInputField::bIsinBounds(sf::Vector2f _vMousePosition)
{
    if (Sprite.getGlobalBounds().contains(sf::Vector2f(_vMousePosition.x, _vMousePosition.y)))
    {
        if (m_bIsPressed != true) {
            Sprite.setTexture(m_HoverTexture);
            SetState("Hover");
        }
        m_bIsHovering = true;
        /*std::cout << "MousedOverButton" << std::endl;*/

        if (m_Label == "Input Value")
        {
            SetLabel("");
        }
        else
        {
            SetLabel(m_Label);
        }
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

        if (m_Label == "")
        {
            SetLabel("Input Value");
        }
        else
        {
            SetLabel(m_Label);
        }
        return false;
    }
}

void CInputField::SetLabel(std::string _label)
{
    std::string oldLabel = m_Label;
    std::string oldClickLabel = m_OnClickLabel;
    if (_label != m_OnClickLabel && _label != m_HoverLabel) {
        m_Label = _label;
    }
    if (m_OnClickLabel == oldLabel && _label != m_HoverLabel) {
        m_OnClickLabel = _label;
    }
    if (m_HoverLabel == oldLabel && _label != oldClickLabel) {
        m_HoverLabel = _label;
    }
    m_tLabel.setString(_label);
    m_tLabel.setCharacterSize(20);
    m_tLabel.setOrigin(sf::Vector2f(m_tLabel.getGlobalBounds().width / 2, m_tLabel.getGlobalBounds().height / 2));
}

void CInputField::SetState(std::string type)
{
    if (type == "Idle") {
        Sprite.setTexture(m_IdleTexture);
    }
    else if (type == "Hover") {
        Sprite.setTexture(m_HoverTexture);
    }
}

void CInputField::SetPosition(float newX, float newY)
{
    Sprite.setPosition(sf::Vector2f(newX, newY));
    m_tLabel.setPosition(sf::Vector2f(newX, newY));
}

std::string CInputField::removeLastChar(std::string s)
{
    {
        if (s == "" || s.length() == 0) {
            return s;
        }
        return s.std::string::substr(0, s.length() - 1);
    }
}

