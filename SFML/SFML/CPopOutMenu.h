#pragma once
#pragma warning (disable : 26812) // SILENCE MINION
#include <SFML/gRAPHICS.HPP>
#include <list>
#include <Windows.h>
#include <Wingdi.h>
#include "CButtons.h"
#include "CBrush.h"

class CPopOutMenu
{
public:
	CPopOutMenu(sf::RenderWindow* _RenderWindow);
	~CPopOutMenu();

	void Start();
	void Update();
	void Render();

	void InitColourDialogue();
	void OpenColourDialogue();

	CButtons* m_ButtonList[6];
	CCanvas* m_Canvas;
	CBrush* m_Brush;
	sf::RenderWindow* m_UIWindow;
	
	bool m_bColourIsOpen = false;
private:
	sf::RenderWindow* m_RenderWindow;

	CHOOSECOLOR cc;                 // common dialog box structure 
	COLORREF acrCustClr[16]; // array of custom colors 
	HWND hwnd;                      // owner window
	HBRUSH hbrush;                  // brush handle
	DWORD rgbCurrent;        // initial color selection
	COLORREF cr;
};

