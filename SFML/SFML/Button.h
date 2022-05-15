// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Button.h 
// Description : Button Header File
// Author : William Inman
// Mail : william.inman@mds.ac.nz

#pragma once
#include "Globals.h"

class Button : public sf::Drawable
{
public:
	/// <summary>
	/// UI Button Constructor
	/// </summary>
	/// <param name="_renderWindow"></param>
	/// <param name="_label"></param>
	/// <param name="_font"></param>
	/// <param name="_position"></param>
	/// <param name="_onPressFunction"></param>
	Button(sf::RenderWindow* _renderWindow, std::string_view _label, sf::Font& _font, sf::Vector2f _position, std::function<void()> _onPressFunction);
	
	/// <summary>
	/// UI Button Destructor
	/// </summary>
	~Button();

	/// <summary>
	/// Handles OnClick Event Registration.
	/// To Be Called In Poll Event
	/// </summary>
	/// <param name="_event"></param>
	void EventHandler(sf::Event& _event);

	/// <summary>
	/// Handles Frame by frame functionality
	/// </summary>
	void Update();
private:

	/// <summary>
	/// Draws the button and text to the screen
	/// </summary>
	/// <param name="_target"></param>
	/// <param name="_states"></param>
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	/// <summary>
	/// Shrinks the button text to fit the sprite
	/// </summary>
	void ShrinkTextToFit();

	sf::Texture m_SpriteTexture;
	sf::Sprite m_Sprite;
	sf::Text m_Text;
	std::function<void()> m_OnPressFunctionality = nullptr;
	sf::Vector2f m_MousePosition;
	sf::RenderWindow* m_RenderWindow = nullptr;
	sf::Font m_Font;

	bool m_IsPressed = false;
};

