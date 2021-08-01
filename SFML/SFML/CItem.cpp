#include "CItem.h"
#include <iostream>

CItem::CItem(ITEMTYPE _itemType)
{
	ItemType = _itemType;
	ItemName = 1.0f;
	switch (ItemType)
	{
	case SWORD:
	{
		
		if (m_tTexture.loadFromFile("Images/Sword.png"))
		{
			m_tTexture.setSmooth(true);
			std::cout << "Loaded SWORD Texture" << std::endl;
		}
		m_sSprite.setTexture(m_tTexture);
		m_sSprite.setOrigin(m_sSprite.getGlobalBounds().width / 2, m_sSprite.getGlobalBounds().height / 2);
		break;
	}
	case SHIELD:
	{
		if (m_tTexture.loadFromFile("Images/ShieldFront.png"))
		{
			m_tTexture.setSmooth(true);
			std::cout << "Loaded SHIELD Texture" << std::endl;
		}
		m_sSprite.setTexture(m_tTexture);
		m_sSprite.setOrigin(m_sSprite.getGlobalBounds().width / 2, m_sSprite.getGlobalBounds().height / 2);
		break;
	}
	}
}

CItem::~CItem()
{
}

void CItem::Render(sf::RenderWindow* _renderWindow)
{
	_renderWindow->draw(m_sSprite);
}
