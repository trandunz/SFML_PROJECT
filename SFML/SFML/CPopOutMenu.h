#pragma once
#include <SFML/gRAPHICS.HPP>
#include <list>
#include "CButtons.h"
#include "CBrush.h"
#include "CCanvas.h"

class CPopOutMenu
{
public:
	CPopOutMenu(sf::RenderWindow* _RenderWindow);
	~CPopOutMenu();

	void Start();
	void Update();
	void Render();
	CButtons* m_ButtonList[5];
	CCanvas* m_Canvas;
	CBrush* m_Brush;
	sf::RenderWindow* m_UIWindow;
	

private:
	sf::RenderWindow* m_RenderWindow;
	

};

