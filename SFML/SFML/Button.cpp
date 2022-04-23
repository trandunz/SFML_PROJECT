#include "Button.h"
Button::Button(sf::RenderWindow* _renderWindow, std::string_view _label, sf::Font& _font, sf::Vector2f _position, std::function<void()> _onPressFunction)
{
	m_OnPressFunctionality = _onPressFunction;
	m_RenderWindow = _renderWindow;
	m_Font = _font;
	m_Text.setString(_label.data());
	m_Text.setFillColor(sf::Color::Black);
	m_Text.setOutlineColor(sf::Color::White);
	m_Text.setOutlineThickness(1.0f);
	m_Text.setFont(_font);
	m_Text.setOrigin(m_Text.getGlobalBounds().width / 2, m_Text.getGlobalBounds().height / 1.5f);
	m_SpriteTexture.loadFromFile("Resources/Textures/Button.png");
	m_Sprite.setTexture(m_SpriteTexture, true);
	m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2, m_Sprite.getGlobalBounds().height / 2);
	m_Sprite.setPosition(_position);

	ShrinkTextToFit();
}

Button::~Button()
{
	m_OnPressFunctionality = nullptr;
	m_RenderWindow = nullptr;
}

void Button::EventHandler(sf::Event& _event)
{
	if (m_Sprite.getGlobalBounds().contains(m_MousePosition))
	{
		m_Sprite.setScale({ 1.1f, 1.1f });

		if (_event.type == sf::Event::MouseButtonPressed)
		{
			m_IsPressed = true;
		}
	}
	else
	{
		m_Sprite.setScale({ 1.0f, 1.0f });
	}
}

void Button::Update()
{
	m_MousePosition = (sf::Vector2f)sf::Mouse::getPosition(*m_RenderWindow);
	m_Text.setPosition(m_Sprite.getPosition());

	if (m_IsPressed)
	{
		m_OnPressFunctionality();
		m_Sprite.setScale({ 1.0f, 1.0f });
		m_IsPressed = false;
	}
	
}

void Button::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Sprite, _states);
	_target.draw(m_Text, _states);
}

void Button::ShrinkTextToFit()
{
	float i = (m_Sprite.getGlobalBounds().width - 20) / m_Text.getGlobalBounds().width;
	i = i < 1 ? i : 1;
	m_Text.setScale({ i , 1});
}
