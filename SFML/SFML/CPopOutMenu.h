#pragma once
#pragma warning (disable : 26812) // SILENCE MINION
#include <SFML/gRAPHICS.HPP>
#include <list>
#include <Windows.h>
#include <Wingdi.h>
#include "CButtons.h"
#include "CBrush.h"
#include "CInputField.h"

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

	void CreateBrushButtons();
	void CustomBrushButtons();

	void InputButtonUpdate(sf::Event _event, int _index);

	void CreateShapeButtons();

	void CreateTabMenuButtons();

	void Save();

	CButtons* m_BrushButtonList[11];
	CButtons* m_ShapeButtonList[11];
	CButtons* m_CanvasButtonList[9];
	CInputField* m_InputList[2];
	CCanvas* m_Canvas;
	CBrush* m_Brush;
	sf::RenderWindow* m_UIWindow;
	
	bool m_bColourIsOpen = false;
	bool m_bBrushMenu;
	bool m_bSaveMenu;
	bool m_bCustomBrush;
private:
	

	sf::RenderWindow* m_RenderWindow;

	CHOOSECOLOR cc;                 // common dialog box structure 
	COLORREF acrCustClr[16]; // array of custom colors 
	HWND hwnd;                      // owner window
	HBRUSH hbrush;                  // brush handle
	DWORD rgbCurrent;        // initial color selection
	COLORREF cr;

	sf::RectangleShape m_BackGround;
	sf::RectangleShape m_BrushBackGround;
	sf::RectangleShape m_CustomBrushBG;
	sf::CircleShape m_bCustBrushPreview;
};

