//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CPopOutMenu.h
// Description : CPopOutMenu Header file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

#pragma once
#pragma warning (disable : 26812) // SILENCE MINION
#include <SFML/Graphics.hpp>
#include <list>
#include <Windows.h>
#include <Wingdi.h>
#include <ShObjIdl.h>
#include <Shlwapi.h>
#include <atlbase.h>

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
	void InputButtonUpdate(sf::Event _event, int _index);
	void Render();

	void InputButtonHoverUpdates(sf::Event _event);

	void InitColourDialogue();
	void OpenColourDialogue();

	void CreateBrushButtons();

	void CustomBrushButtons();
	void CustomShapeButtons();

	void CreateShapeButtons();
	void CreateTabMenuButtons();
	void CreateSaveMenuButtons();
	void CreateCanvasMenuButtons();

	void Save(std::string& _name);
	void Load();

	void CreateSnip();

	void OpenFileDialogue(sf::RectangleShape& _canvas);
	void SaveFileDialogue();

	void ShapesMenuFillCheck();

	CButtons* m_BrushButtonList[11] = {};
	CButtons* m_ShapeButtonList[12] = {};
	CButtons* m_CanvasButtonList[9] = {};
	CButtons* m_SaveMenuButtonList[3] = {};
	CInputField* m_InputList[6];
	CCanvas* m_Canvas;
	CBrush* m_Brush;
	CShapes* m_Shape;
	sf::RenderWindow* m_UIWindow;
	sf::Color tempColour;
	
	bool m_bColourIsOpen = false;
	bool m_bBrushMenu;
	bool m_bShapeMenu;
	bool m_bSaveMenu;
	bool m_bCanvasMenu;
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

	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
	HWND hwndFile;              // owner window
	HANDLE hf;              // file handle
	HRESULT hr;
	sf::Texture* imageTex;


	sf::RectangleShape m_BackGround;
	sf::RectangleShape m_BrushBackGround;
	sf::RectangleShape m_CustomBrushBG;
	sf::CircleShape m_bCustBrushPreview;
	sf::CircleShape m_bCustShapePreview;
	sf::RectangleShape m_SaveMenuPreviewBG;

	sf::RectangleShape m_SaveMenuPreview;

	sf::RenderTexture* m_Snip;
};

