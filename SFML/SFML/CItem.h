#pragma once
#include <SFML/GRAPHICS.HPP>
class CItem
{
public :

	enum ITEMTYPE
	{
		SWORD,
		SHIELD,
		POTION,
		KEY
	};

	ITEMTYPE ItemType;
	

	CItem(ITEMTYPE _itemType);
	~CItem();

	void Render(sf::RenderWindow* _renderWindow);

	sf::Sprite m_sSprite;
	sf::Texture m_tTexture;
	float ItemName;
};

