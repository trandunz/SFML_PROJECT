#pragma once
#include "Globals.h"

class Button : public sf::Drawable
{
public:
	Button(sf::RenderWindow* _renderWindow, std::string_view _label, sf::Font& _font, sf::Vector2f _position, std::function<void()> _onPressFunction);
	~Button();

	void EventHandler(sf::Event& _event);
	void Update();
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	sf::Texture m_SpriteTexture;
	sf::Sprite m_Sprite;
	sf::Text m_Text;
	std::function<void()> m_OnPressFunctionality = nullptr;
	sf::Vector2f m_MousePosition;
	sf::RenderWindow* m_RenderWindow = nullptr;
	sf::Font m_Font;

	bool m_IsPressed = false;
};

