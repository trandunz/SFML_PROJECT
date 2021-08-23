#pragma once
#pragma warning (disable : 26812) // SILENCE MINION
#include <SFML/gRAPHICS.HPP>
#include <list>
#include <Windows.h>
#include <Wingdi.h>
#include "CButtons.h"
#include "CBrush.h"
#include "CShapes.h"
#include "CInputField.h"

class CPopOutMenu
{
public:
	CPopOutMenu(sf::RenderWindow* _RenderWindow);
	~CPopOutMenu();

	void Start();
	void Update();
	void Render();

	void InputButtonHoverUpdates(sf::Event _event);

	void InitColourDialogue();
	void OpenColourDialogue();

	void CreateBrushButtons();
	void CustomBrushButtons();
	void CustomShapeButtons();

	void InputButtonUpdate(sf::Event _event, int _index);

	void CreateShapeButtons();

	void CreateTabMenuButtons();

	void Save();

	void ShapesMenuFillCheck();

	CButtons* m_BrushButtonList[11];
	CButtons* m_ShapeButtonList[11];
	CButtons* m_CanvasButtonList[9];
	CInputField* m_InputList[4];
	CCanvas* m_Canvas;
	CBrush* m_Brush;
	CShapes* m_Shape;
	sf::RenderWindow* m_UIWindow;
	sf::Color tempColour;
	
	bool m_bColourIsOpen = false;
	bool m_bBrushMenu;
	bool m_bShapeMenu;
	bool m_bSaveMenu;
	bool m_bCustomBrush;
	bool m_bShapeFillColour;

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
	sf::CircleShape m_bCustShapePreview;
};

