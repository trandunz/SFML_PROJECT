//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CPopOutMenu.cpp
// Description : CPopOutMenu Implementation file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

// Non-Local Includes

// Local Includes
#include "CPopOutMenu.h"

/// <summary>
/// PopOutMenu Constructor. Takes in an sf::RenderWindow* (Intended To Be The Main Render Window With Canvas e.t.c).
/// </summary>
CPopOutMenu::CPopOutMenu(sf::RenderWindow* _RenderWindow)
{
	// UI Essentials Creation
	m_BackGround = sf::RectangleShape(sf::Vector2f(320, 720));
	m_BrushBackGround = sf::RectangleShape(sf::Vector2f(300, 640)); // Brush Menu BG
	m_CustomBrushBG = sf::RectangleShape(sf::Vector2f(280, 305)); // Custom Brush BG
	m_SaveMenuPreviewBG = sf::RectangleShape(sf::Vector2f(280, 495)); // Save Menu Preview BG
	m_bCustBrushPreview = sf::CircleShape(80);	// Custom Brush Preview
	m_bCustShapePreview = sf::CircleShape(70); // Custom Shape Preview

	m_BrushBackGround.setFillColor(sf::Color(204, 204, 204)); // Grey
	m_CustomBrushBG.setFillColor(sf::Color(190, 190, 190)); // Darker Grey
	m_SaveMenuPreviewBG.setFillColor(sf::Color(190, 190, 190)); // Darker Grey
	m_bCustBrushPreview.setFillColor(sf::Color(209, 28, 255)); // Purple
	m_bCustShapePreview.setFillColor(sf::Color(209, 28, 255)); // Purple
	m_bCustShapePreview.setOutlineColor(sf::Color(209, 28, 255)); // Purple

	// Set Origin's to center
	m_CustomBrushBG.setOrigin(m_CustomBrushBG.getGlobalBounds().width / 2, m_CustomBrushBG.getGlobalBounds().height / 2);
	m_SaveMenuPreviewBG.setOrigin(m_SaveMenuPreviewBG.getGlobalBounds().width / 2, m_SaveMenuPreviewBG.getGlobalBounds().height / 2);
	m_bCustBrushPreview.setOrigin(m_bCustBrushPreview.getGlobalBounds().width / 2, m_bCustBrushPreview.getGlobalBounds().height / 2);
	m_bCustShapePreview.setOrigin(m_bCustShapePreview.getGlobalBounds().width / 2, m_bCustShapePreview.getGlobalBounds().height / 2);

	// Positioning
	m_BrushBackGround.setPosition(m_BrushBackGround.getSize().x / 30, m_BrushBackGround.getSize().y / 9);
	m_CustomBrushBG.setPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.175);
	m_SaveMenuPreviewBG.setPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.425);
	m_bCustBrushPreview.setPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.075);
	m_bCustShapePreview.setPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.075);

	// Menu Initialization
	m_Canvas = nullptr;
	m_Brush = nullptr;
	m_RenderWindow = _RenderWindow;

	// Render Window Creation
	m_UIWindow = new sf::RenderWindow(sf::VideoMode(320, 720), "Tools", (sf::Style::Titlebar));
	m_UIWindow->setFramerateLimit((unsigned)120);
	
	// Colour Dialogue Initialization
	InitColourDialogue();
}

/// <summary>
/// PopOutMenu Destructor
/// </summary>
CPopOutMenu::~CPopOutMenu()
{
	// CleanUp Brush Buttons
	for (int i = 0; i < 11; i++)
	{
		delete m_BrushButtonList[i];
		m_BrushButtonList[i] = nullptr;
		/*std::cout << "PopedFront" << std::endl;*/
	}

	// CleanUp Shape Buttons
	for (int i = 0; i < 12; i++)
	{
		delete m_ShapeButtonList[i];
		m_ShapeButtonList[i] = nullptr;
		/*std::cout << "PopedFront" << std::endl;*/
	}

	// CleanUp InputLists
	for (int i = 0; i < 4; i++)
	{
		delete m_InputList[i];
		m_InputList[i] = nullptr;
		/*std::cout << "PopedFront" << std::endl;*/
	}

	// CleanUp Save Menu Buttons
	for (int i = 0; i < 3; i++)
	{
		delete m_SaveMenuButtonList[i];
		m_SaveMenuButtonList[i] = nullptr;
		/*std::cout << "PopedFront" << std::endl;*/
	}

	// Object and Pointer CleanUp
	delete m_Canvas;
	delete m_Brush;
	delete m_Shape;
	m_UIWindow = nullptr;
	m_Brush = nullptr;
	m_Shape = nullptr;
	m_Canvas = nullptr;
	m_RenderWindow = nullptr;
}

/// <summary>
/// Start Function For PopOutMenu (Intended To Be Called Before Update).
/// </summary>
void CPopOutMenu::Start()
{
	// Essentials Creation
	m_Canvas = new CCanvas(m_RenderWindow, sf::Vector2f(1000.0f, 1000.0f));
	m_Brush = new CBrush(m_RenderWindow, m_Canvas);
	m_Shape = new CShapes(m_RenderWindow, m_Canvas);

	// Essentials Initialization
	m_Brush->m_BrushType = m_Brush->BRUSHTYPE::DEFAULT;
	m_Brush->m_BushSize = 1;
	m_Brush->m_SideCount = 100;
	m_Brush->m_Rotation = 0.0f;

	m_Shape->m_ShapeType = m_Shape->SHAPETYPE::DEFAULT;
	m_Shape->m_SideCount = 100;
	m_Shape->m_Rotation = 0.0f;
	

	// Button Creation
	CreateTabMenuButtons();
	CreateBrushButtons();
	CreateShapeButtons();
	CustomBrushButtons();
	CustomShapeButtons();
	CreateSaveMenuButtons();

	// Initialize Bools
	m_bBrushMenu = false;
	m_bSaveMenu = false;
	m_bCustomBrush = false;
	m_bShapeMenu = false;
	m_bShapeFillColour = false;

	// Checks
	ShapesMenuFillCheck();

	// Render
	Render();
}

/// <summary>
/// Hover Update Check For all Input Fields. Takes in an sf::Event.
/// </summary>
/// <param name="_event"></param>
void CPopOutMenu::InputButtonHoverUpdates(sf::Event _event)
{
	if (m_bBrushMenu && m_InputList[0]->bIsinBounds(m_InputList[0]->GetMousePosition()))
	{
		InputButtonUpdate(_event, 0);
	}
	else if (m_bBrushMenu && m_bCustomBrush && m_InputList[1]->bIsinBounds(m_InputList[1]->GetMousePosition()))
	{
		InputButtonUpdate(_event, 1);
	}

	if (m_bShapeMenu && m_InputList[2]->bIsinBounds(m_InputList[2]->GetMousePosition()))
	{
		InputButtonUpdate(_event, 2);
	}
	else if (m_bShapeMenu && m_bCustomBrush && m_InputList[3]->bIsinBounds(m_InputList[3]->GetMousePosition()))
	{
		InputButtonUpdate(_event, 3);
	}
}

/// <summary>
/// Update Loop For PopOutMenu.
/// </summary>
void CPopOutMenu::Update()
{
	sf::Event UIEvent;
	while (m_UIWindow->pollEvent(UIEvent))
	{
		// Debug
		std::cout << m_BrushButtonList[2]->Sprite.getPosition().x<< std::endl;
		std::cout << m_BrushButtonList[2]->Sprite.getPosition().y << std::endl;
		/*std::cout << m_ButtonList[0]->GetMousePosition().x << std::endl;
		std::cout << m_ButtonList[0]->GetMousePosition().y << std::endl;*/

		// Mouse Click Button Actions
		if (UIEvent.type == sf::Event::MouseButtonPressed)
		{
			if (m_BrushButtonList[0]->bIsinBounds(m_BrushButtonList[0]->GetMousePosition()))
			{
				m_bBrushMenu = !m_bBrushMenu;
				m_bShapeMenu = false;
				m_bSaveMenu = false;
				std::cout << "Brush Menu Pressed" << std::endl;
			}
			if (m_BrushButtonList[1]->bIsinBounds(m_BrushButtonList[1]->GetMousePosition()))
			{
				OpenColourDialogue();
				
			}
			if (m_BrushButtonList[2]->bIsinBounds(m_BrushButtonList[2]->GetMousePosition()))
			{
				m_bShapeMenu = false;
				m_bBrushMenu = false;
				m_bSaveMenu = false;
				std::cout << "Canvas Menu Pressed" << std::endl;
			}
			if (m_BrushButtonList[3]->bIsinBounds(m_BrushButtonList[3]->GetMousePosition()))
			{
				m_bShapeMenu = !m_bShapeMenu;
				m_bBrushMenu = false;
				m_bSaveMenu = false;
				std::cout << "Shape Menu Pressed" << std::endl;
				InputButtonUpdate(UIEvent, 2);
			}
			if (m_BrushButtonList[10]->bIsinBounds(m_BrushButtonList[10]->GetMousePosition()))
			{
				m_bSaveMenu = !m_bSaveMenu;
				m_bShapeMenu = false;
				m_bBrushMenu = false;
				/*Save();*/
				std::cout << "Save Menu Pressed" << std::endl;
			}

			if (m_bBrushMenu)
			{
				if (m_BrushButtonList[4]->bIsinBounds(m_BrushButtonList[4]->GetMousePosition()))
				{
					m_Brush->m_BrushType = m_Brush->BRUSHTYPE::SQUARE;
					m_bCustomBrush = false;
				}
				if (m_BrushButtonList[5]->bIsinBounds(m_BrushButtonList[5]->GetMousePosition()))
				{
					m_Brush->m_BrushType = m_Brush->BRUSHTYPE::CIRCLE;
					m_bCustomBrush = false;
				}
				if (m_BrushButtonList[6]->bIsinBounds(m_BrushButtonList[6]->GetMousePosition()))
				{
					m_Brush->m_BrushType = m_Brush->BRUSHTYPE::TRIANGLE;
					m_bCustomBrush = false;
				}
				if (m_BrushButtonList[7]->bIsinBounds(m_BrushButtonList[7]->GetMousePosition()))
				{
					m_Brush->m_BrushType = m_Brush->BRUSHTYPE::CUSTOM;
					m_bCustomBrush = !m_bCustomBrush;
				}
			}

			if (m_bShapeMenu)
			{
				if (m_ShapeButtonList[0]->bIsinBounds(m_BrushButtonList[0]->GetMousePosition()))
				{
					m_bShapeFillColour = !m_bShapeFillColour;
					m_ShapeButtonList[0]->m_bIsPressed = !m_ShapeButtonList[0]->m_bIsPressed;
					std::cout << "Fill Button Pressed" << std::endl;

					ShapesMenuFillCheck();
				}
				if (m_ShapeButtonList[4]->bIsinBounds(m_BrushButtonList[4]->GetMousePosition()))
				{ 
					m_Shape->m_ShapeType = m_Shape->SHAPETYPE::SQUARE;
					m_Shape->m_SideCount = 4;
					m_Shape->m_Rotation = 45;
					InputButtonUpdate(UIEvent, 3);
					m_bCustomBrush = false;
				}
				if (m_ShapeButtonList[11]->bIsinBounds(m_ShapeButtonList[11]->GetMousePosition()))
				{
					m_Shape->m_ShapeType = m_Shape->SHAPETYPE::LINE;
					m_bCustomBrush = false;
				}
				
				if (m_ShapeButtonList[5]->bIsinBounds(m_BrushButtonList[5]->GetMousePosition()))
				{
					m_Shape->m_ShapeType = m_Shape->SHAPETYPE::CIRCLE;
					m_Shape->m_SideCount = 100;
					m_Shape->m_Rotation = 0;
					InputButtonUpdate(UIEvent, 3);
					m_bCustomBrush = false;
				}
				if (m_ShapeButtonList[6]->bIsinBounds(m_BrushButtonList[6]->GetMousePosition()))
				{
					m_Shape->m_ShapeType = m_Shape->SHAPETYPE::TRIANGLE;
					m_Shape->m_SideCount = 3;
					m_Shape->m_Rotation = 0;
					InputButtonUpdate(UIEvent, 3);
					m_bCustomBrush = false;
				}
				if (m_ShapeButtonList[7]->bIsinBounds(m_BrushButtonList[7]->GetMousePosition()))
				{
					m_Shape->m_ShapeType = m_Shape->SHAPETYPE::CUSTOM;
					m_Shape->m_Rotation = 0;
					m_bCustShapePreview.setPointCount(utils::StringUtils::parse<int>(m_InputList[3]->m_Label));
					m_Shape->m_SideCount = utils::StringUtils::parse<int>(m_InputList[3]->m_Label);
					InputButtonUpdate(UIEvent, 3);
					m_bCustomBrush = !m_bCustomBrush;
				}
			}

			if (m_bSaveMenu)
			{
				if (m_SaveMenuButtonList[0]->bIsinBounds(m_SaveMenuButtonList[0]->GetMousePosition()))
				{
					Save();
				}
				if (m_SaveMenuButtonList[1]->bIsinBounds(m_SaveMenuButtonList[1]->GetMousePosition()))
				{
					std::cout << "Load" << std::endl;
				}
			}
		}

		// Input List Updates On Key Press
		if ((UIEvent.type == sf::Event::KeyPressed))
		{
			m_InputList[0]->Update();
			m_InputList[1]->Update();
			m_InputList[2]->Update();
			m_InputList[3]->Update();
			Render();
		}

		// Colour Menu Hotkey
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			OpenColourDialogue();
			std::cout << "Colour Menu ShortCut" << std::endl;
		}

		// Shapes Menu Hotkey
		if (UIEvent.type == sf::Event::KeyPressed && UIEvent.key.code == sf::Keyboard::A)
		{
			m_bShapeMenu = !m_bShapeMenu;
			m_bBrushMenu = false;
			std::cout << "Shape Menu ShortCut" << std::endl;
		}

		// Button Updates
		for (int i = 0; i < 11; i++)
		{
			m_BrushButtonList[i]->Update();
		}
		for (int i = 0; i < 12; i++)
		{
			if (m_ShapeButtonList[i] != nullptr)
			{
				m_ShapeButtonList[i]->Update();
			}
		}
		InputButtonHoverUpdates(UIEvent);
		m_SaveMenuButtonList[0]->Update();
		m_SaveMenuButtonList[1]->Update();
		m_SaveMenuButtonList[2]->Update();

		//
		//m_InputList[0]->Update();
		//m_InputList[1]->Update();
		//m_InputList[2]->Update();
		//m_InputList[3]->Update();
		//

		// Check For Fill Colour For Shapes
		m_bCustBrushPreview.setFillColor(m_Brush->m_Colour);
		if (m_bShapeFillColour)
		{
			m_bCustShapePreview.setFillColor(m_Brush->m_Colour);
			m_bCustShapePreview.setOutlineThickness(10);
			m_bCustShapePreview.setOutlineColor(sf::Color::Transparent);

		}
		else if (m_bShapeFillColour == false)
		{
			m_bCustShapePreview.setFillColor(sf::Color::Transparent);
			m_bCustShapePreview.setOutlineThickness(10);
			
			m_bCustShapePreview.setOutlineColor(m_Brush->m_Colour);
		}

		// Render
		Render();
	}
}

/// <summary>
/// Performs Update Checks for specified Input Button at _index. This function takes in an f::event and an index.
/// </summary>
/// <param name="_event"></param>
/// <param name="_index"></param>s
void CPopOutMenu::InputButtonUpdate (sf::Event _event, int _index)
{

	if (_event.type == sf::Event::TextEntered && m_InputList[_index]->m_Label.size() < 3 && isdigit(_event.text.unicode))
	{

		m_InputList[_index]->m_Label += _event.text.unicode;
		if (_index == 0)
		{
			m_Brush->m_BushSize = utils::StringUtils::parse<int>(m_InputList[_index]->m_Label);
		}
		else if (_index == 1)
		{
			m_bCustBrushPreview.setPointCount(utils::StringUtils::parse<int>(m_InputList[_index]->m_Label));
			m_Brush->m_SideCount = utils::StringUtils::parse<int>(m_InputList[_index]->m_Label);
		}
		else if (_index == 2)
		{
			m_bCustShapePreview.setOutlineThickness(utils::StringUtils::parse<float>(m_InputList[_index]->m_Label));
			m_Shape->m_OutlineThickness = utils::StringUtils::parse<float>(m_InputList[_index]->m_Label);
		}
		else if (_index == 3)
		{
			m_bCustShapePreview.setPointCount(utils::StringUtils::parse<int>(m_InputList[_index]->m_Label));
			m_Shape->m_SideCount = utils::StringUtils::parse<int>(m_InputList[_index]->m_Label);
		}

	}
	else if (_event.type == sf::Event::TextEntered && m_InputList[_index]->m_Label.size() > 0 && _event.text.unicode == 8)
	{
		m_InputList[_index]->m_Label = m_InputList[_index]->removeLastChar(m_InputList[_index]->m_Label);
		if (m_InputList[_index]->m_Label == "")
		{
			if (_index == 0)
			{
				m_Brush->m_BushSize = 1;
			}
			else if(_index == 1)
			{
				m_bCustBrushPreview.setPointCount(100);
				m_Brush->m_SideCount = 100;
			}
			else if (_index == 2)
			{
				m_bCustShapePreview.setOutlineThickness(1);
				m_Shape->m_OutlineThickness = 1;
			}
			else if (_index == 3)
			{
				m_bCustShapePreview.setPointCount(100);
				m_Shape->m_SideCount = 100;
				// set shape side count
			}
			
		}
		else
		{
			if (_index == 0)
			{
				m_Brush->m_BushSize = utils::StringUtils::parse<int>(m_InputList[_index]->m_Label);
			}
			else if (_index == 1)
			{
				m_bCustBrushPreview.setPointCount(utils::StringUtils::parse<int>(m_InputList[_index]->m_Label));
				m_Brush->m_SideCount = utils::StringUtils::parse<int>(m_InputList[_index]->m_Label);
			}
			else if (_index == 2)
			{
				// outline thickness
				m_bCustShapePreview.setOutlineThickness(utils::StringUtils::parse<float>(m_InputList[_index]->m_Label));
				m_Shape->m_OutlineThickness = utils::StringUtils::parse<float>(m_InputList[_index]->m_Label);
			}
			else if (_index == 3)
			{
				m_bCustShapePreview.setPointCount(utils::StringUtils::parse<int>(m_InputList[_index]->m_Label));
				m_Shape->m_SideCount = utils::StringUtils::parse<int>(m_InputList[_index]->m_Label);
			}
			
		}
		
	}

	if (m_bCustBrushPreview.getPointCount() == 1 || m_bCustBrushPreview.getPointCount() == 2 || m_bCustBrushPreview.getPointCount() == 0)
	{
		m_bCustBrushPreview.setPointCount(100);
		m_Brush->m_SideCount = 100;
	}

	if (m_bCustShapePreview.getPointCount() == 1 || m_bCustShapePreview.getPointCount() == 2 || m_bCustShapePreview.getPointCount() == 0)
	{
		m_bCustShapePreview.setPointCount(100);
		m_Shape->m_SideCount = 100;
	}

	if (m_Brush->m_BushSize == 0)
	{
		m_Brush->m_BushSize = 1;
	}

	if (m_Shape->m_OutlineThickness == 0)
	{
		m_Shape->m_OutlineThickness = 1;
	}
	/*if (m_bCustShapePreview.getOutlineThickness() <= 0)
	{
		m_bCustShapePreview.setOutlineThickness(0.01f);
	}*/
}

/// <summary>
/// Render Definition For PopOutMenu.
/// </summary>
void CPopOutMenu::Render()
{
	// Clear Render Window
	m_UIWindow->clear();

	// Background (white)
	m_UIWindow->draw(m_BackGround);

	// Brush Menu
	if (m_bBrushMenu)
	{
		// Sub Menu Background
		m_UIWindow->draw(m_BrushBackGround);
		
		// Custom Brush
		if (m_bCustomBrush)
		{
			m_UIWindow->draw(m_CustomBrushBG);
			m_BrushButtonList[9]->RenderOnlyLabel();
			m_InputList[1]->Render();
			m_UIWindow->draw(m_bCustBrushPreview);
		}
	}

	// Shape Manu
	if (m_bShapeMenu)
	{
		// Sub Menu BackGround
		m_UIWindow->draw(m_BrushBackGround);

		// Custom Shape (Shared Bool With Custom Brush)
		if (m_bCustomBrush)
		{
			m_UIWindow->draw(m_CustomBrushBG);	// Custom Shape BG
			m_ShapeButtonList[9]->RenderOnlyLabel();	// Custom Shape Sides Text Indicator
			m_InputList[3]->Render();	// Custom Shape Side Input Field
			m_UIWindow->draw(m_bCustShapePreview);	// Custom Shape Preview
		}
	}

	// Save Menu
	if (m_bSaveMenu)
	{
		// Sub Menu BackGround
		m_UIWindow->draw(m_BrushBackGround);

		// Save Preview
		m_UIWindow->draw(m_SaveMenuPreviewBG); // Sapve Preview BG
	}

	// Save Menu Buttons
	if (m_bSaveMenu)
	{
		m_SaveMenuButtonList[0]->Render();
		m_SaveMenuButtonList[1]->Render();
		m_SaveMenuButtonList[2]->RenderOnlyLabel();
	}

	// Shape Menu Buttons
	if (m_bShapeMenu)
	{

		m_ShapeButtonList[0]->Render(); // Fill bool button
		m_ShapeButtonList[1]->Render();  // colour button

		for (int i = 4; i < 8; i++)
		{
			m_ShapeButtonList[i]->Render();
		}
		m_ShapeButtonList[11]->Render(); // Line Button

		m_InputList[2]->Render(); // Outline Thickness Input Field

		m_ShapeButtonList[8]->RenderOnlyLabel();	// Outline Thickness Text Indicator
		m_ShapeButtonList[10]->RenderOnlyLabel();	// Fill Bool Text Indicator
	}
	
	// Brush Menu Buttons
	if (m_bBrushMenu)
	{


		m_BrushButtonList[1]->Render();  // colour button
		for (int i = 3; i < 8; i++)
		{
			m_BrushButtonList[i]->Render();
		}

		m_InputList[0]->Render(); // Brush Size Input Field

		m_BrushButtonList[8]->RenderOnlyLabel();	// Brush Size Text Indicator
	}

	// Tab Menu Buttons
	m_BrushButtonList[0]->Render(); // brush button
	m_BrushButtonList[2]->Render(); // Canvas button
	m_BrushButtonList[3]->Render(); // Shapes button
	m_BrushButtonList[10]->Render(); // Save button

	// Display
	m_UIWindow->display();
}

/// <summary>
/// Initializes The PopUp Colour Dialogue Window.
/// </summary>
void CPopOutMenu::InitColourDialogue()
{
	// Initialize CHOOSECOLOR
	hwnd = m_UIWindow->getSystemHandle();
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwnd;
	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
}

/// <summary>
/// Opens The PopUp Colour Dialogue Window.
/// </summary>
void CPopOutMenu::OpenColourDialogue()
{
	if (ChooseColor(&cc) == TRUE)
	{
		cr = cc.rgbResult;
		tempColour.r = GetRValue(cr);
		tempColour.g = GetGValue(cr);
		tempColour.b = GetBValue(cr);
		m_Brush->SetActiveColour(tempColour);
		ShapesMenuFillCheck();
	}
	
	/*m_bColourIsOpen = !m_bColourIsOpen;*/
}

/// <summary>
/// Brush Menu Buttons Creation And Initialization.
/// </summary>
void CPopOutMenu::CreateBrushButtons()
{
	CInputField* BrushSize = new CInputField(m_UIWindow);
	BrushSize->SetPosition(m_UIWindow->getSize().x / 2 + m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 6);

	CButtons* BrushSizeLabel = new CButtons(m_UIWindow);
	BrushSizeLabel->SetLabel("Brush Size:");
	BrushSizeLabel->SetPosition(m_UIWindow->getSize().x / 2 - m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 6);

	CButtons* Colour = new CButtons(m_UIWindow);
	Colour->SetLabel("Colour");
	Colour->SetPosition(m_UIWindow->getSize().x / 2 + m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 4);

	CButtons* Square = new CButtons(m_UIWindow);
	Square->SetLabel("Square");
	Square->SetPosition(m_UIWindow->getSize().x / 2 - m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 4);
	CButtons* Circle = new CButtons(m_UIWindow);
	Circle->SetLabel("Circle");
	Circle->SetPosition(m_UIWindow->getSize().x / 2 - m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 3);
	CButtons* Triangle = new CButtons(m_UIWindow);
	Triangle->SetLabel("Triangle");
	Triangle->SetPosition(m_UIWindow->getSize().x / 2 - m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 2.4);
	CButtons* Custom = new CButtons(m_UIWindow);
	Custom->SetLabel("Custom");
	Custom->SetPosition(m_UIWindow->getSize().x / 2 - m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 2);

	m_BrushButtonList[1] = Colour;

	m_BrushButtonList[4] = Square;
	m_BrushButtonList[5] = Circle;
	m_BrushButtonList[6] = Triangle;
	m_BrushButtonList[7] = Custom;

	m_BrushButtonList[8] = BrushSizeLabel;

	m_InputList[0] = BrushSize;
}

/// <summary>
/// Custom Brush Menu Buttons Creation And Initialization.
/// </summary>
void CPopOutMenu::CustomBrushButtons()
{
	CButtons* SidesLabel = new CButtons(m_UIWindow);
	SidesLabel->SetLabel("Number Of Sides");
	SidesLabel->SetPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.55);
	m_BrushButtonList[9] = SidesLabel;

	CInputField* SidesInput = new CInputField(m_UIWindow);
	SidesInput->SetPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.35);
	m_InputList[1] = SidesInput;
}

/// <summary>
/// Custom Shape Menu Buttons Creation And Initialization.
/// </summary>
void CPopOutMenu::CustomShapeButtons()
{
	CButtons* SidesLabel = new CButtons(m_UIWindow);
	SidesLabel->SetLabel("Number Of Sides");
	SidesLabel->SetPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.55);
	m_ShapeButtonList[9] = SidesLabel;

	CInputField* SidesInput = new CInputField(m_UIWindow);
	SidesInput->SetPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.35);
	m_InputList[1] = SidesInput;

	CInputField* SidesInputShape = new CInputField(m_UIWindow);
	SidesInputShape->SetPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.35);
	m_InputList[3] = SidesInputShape;
}

/// <summary>
/// ShapeMenu Buttons Creation And Initialization.
/// </summary>
void CPopOutMenu::CreateShapeButtons()
{
	CInputField* OutLineThickness = new CInputField(m_UIWindow);
	OutLineThickness->SetPosition(m_UIWindow->getSize().x / 2 + m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 6);

	CButtons* OutLineThicButton = new CButtons(m_UIWindow);
	OutLineThicButton->SetLabel("OutLine Thick:");
	OutLineThicButton->SetPosition(m_UIWindow->getSize().x / 2 - m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 6);

	CButtons* Colour = new CButtons(m_UIWindow);
	Colour->SetLabel("Colour");
	Colour->SetPosition(m_UIWindow->getSize().x / 2 + m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 4);

	CButtons* Square = new CButtons(m_UIWindow);
	Square->SetLabel("Square");
	Square->SetPosition(m_UIWindow->getSize().x / 2 - m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 4);
	CButtons* Line = new CButtons(m_UIWindow);
	Line->SetLabel("Line");
	Line->SetPosition(m_UIWindow->getSize().x / 2 + m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 3);
	CButtons* Circle = new CButtons(m_UIWindow);
	Circle->SetLabel("Circle");
	Circle->SetPosition(m_UIWindow->getSize().x / 2 - m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 3);
	CButtons* Triangle = new CButtons(m_UIWindow);
	Triangle->SetLabel("Triangle");
	Triangle->SetPosition(m_UIWindow->getSize().x / 2 - m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 2.4);
	CButtons* Custom = new CButtons(m_UIWindow);
	Custom->SetLabel("Custom");
	Custom->SetPosition(m_UIWindow->getSize().x / 2 - m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 2);
	
	CButtons* BoolLabel = new CButtons(m_UIWindow);
	BoolLabel->SetLabel("Fill");
	BoolLabel->SetPosition(m_UIWindow->getSize().x / 2 + m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 2.4);
	m_ShapeButtonList[10] = BoolLabel;

	CButtons* FillBoolButton = new CButtons(m_UIWindow);
	sf::Texture BoolClickTex;
	sf::Texture BoolIdleTex;
	BoolClickTex.loadFromFile("Images/BoolButtonTrue.png");
	BoolIdleTex.loadFromFile("Images/BoolButton.png");
	FillBoolButton->SetClickTex(BoolClickTex);
	FillBoolButton->SetIdleTex(BoolIdleTex);
	FillBoolButton->SetHoverTex(BoolIdleTex);
	FillBoolButton->Sprite.setOrigin(sf::Vector2f(FillBoolButton->Sprite.getGlobalBounds().width / 2, FillBoolButton->Sprite.getGlobalBounds().height / 2));
	FillBoolButton->SetLabel("");
	FillBoolButton->SetPosition(m_UIWindow->getSize().x / 2 + m_UIWindow->getSize().x / 4.5 + m_UIWindow->getSize().x / 8, m_UIWindow->getSize().y / 2); // Position

	m_ShapeButtonList[0] = FillBoolButton;
	m_ShapeButtonList[1] = Colour;

	m_ShapeButtonList[4] = Square;
	
	m_ShapeButtonList[5] = Circle;
	m_ShapeButtonList[6] = Triangle;
	m_ShapeButtonList[7] = Custom;

	m_ShapeButtonList[8] = OutLineThicButton;
	
	m_ShapeButtonList[11] = Line;
	m_InputList[2] = OutLineThickness;

}

/// <summary>
/// Tab Menu Buttons Creation And Initialization.
/// </summary>
void CPopOutMenu::CreateTabMenuButtons()
{


	CButtons* Brush = new CButtons(m_UIWindow);
	sf::Texture BrushHoverTex;
	sf::Texture BrushIdleTex;
	BrushHoverTex.loadFromFile("Images/BrushIcon.png");
	BrushIdleTex.loadFromFile("Images/BrushIconHover.png");
	Brush->SetHoverTex(BrushHoverTex);
	Brush->SetIdleTex(BrushIdleTex);
	Brush->Sprite.setOrigin(sf::Vector2f(Brush->Sprite.getGlobalBounds().width / 2, Brush->Sprite.getGlobalBounds().height / 2));
	Brush->SetLabel("");
	Brush->SetPosition(m_UIWindow->getSize().x/2 + 80, m_UIWindow->getSize().y / 20); // Position

	CButtons* Canvas = new CButtons(m_UIWindow);
	sf::Texture CanvasHoverTex;
	sf::Texture CanvasIdleTex;
	CanvasHoverTex.loadFromFile("Images/CanvasIconHover.png");
	CanvasIdleTex.loadFromFile("Images/CanvasIcon.png");
	Canvas->SetHoverTex(CanvasHoverTex);
	Canvas->SetIdleTex(CanvasIdleTex);
	Canvas->Sprite.setOrigin(sf::Vector2f(Canvas->Sprite.getGlobalBounds().width / 2, Canvas->Sprite.getGlobalBounds().height / 2));
	Canvas->SetLabel("");
	Canvas->SetPosition(m_UIWindow->getSize().x / 2, m_UIWindow->getSize().y / 20); // Position

	CButtons* Shape = new CButtons(m_UIWindow);
	sf::Texture ShapeHoverTex;
	sf::Texture ShapeIdleTex;
	ShapeHoverTex.loadFromFile("Images/ShapeIconHover.png");
	ShapeIdleTex.loadFromFile("Images/ShapeIcon.png");
	Shape->SetHoverTex(ShapeHoverTex);
	Shape->SetIdleTex(ShapeIdleTex);
	Shape->Sprite.setOrigin(sf::Vector2f(Shape->Sprite.getGlobalBounds().width / 2, Shape->Sprite.getGlobalBounds().height / 2));
	Shape->SetLabel("");
	Shape->SetPosition(m_UIWindow->getSize().x / 4, m_UIWindow->getSize().y / 20); // Position

	CButtons* Save = new CButtons(m_UIWindow);
	sf::Texture SaveHoverTex;
	sf::Texture SaveIdleTex;
	SaveHoverTex.loadFromFile("Images/SaveIconHover.png");
	SaveIdleTex.loadFromFile("Images/SaveIcon.png");
	Save->SetHoverTex(SaveHoverTex);
	Save->SetIdleTex(SaveIdleTex);
	Save->Sprite.setOrigin(sf::Vector2f(Save->Sprite.getGlobalBounds().width / 2, Save->Sprite.getGlobalBounds().height / 2));
	Save->SetLabel("");
	Save->SetPosition(m_UIWindow->getSize().x / 2 + 160, m_UIWindow->getSize().y / 20); // Position

	m_BrushButtonList[0] = Brush;

	m_BrushButtonList[2] = Canvas;
	m_BrushButtonList[3] = Shape;
	m_BrushButtonList[10] = Save;
}

void CPopOutMenu::CreateSaveMenuButtons()
{
	CButtons* Save = new CButtons(m_UIWindow);
	Save->SetLabel("Save");
	Save->SetPosition(m_UIWindow->getSize().x / 2 - m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 6);

	CButtons* Load = new CButtons(m_UIWindow);
	Load->SetLabel("Load");
	Load->SetPosition(m_UIWindow->getSize().x / 2 + m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 6);

	CButtons* PreviewLabel = new CButtons(m_UIWindow);
	PreviewLabel->SetLabel("Image Preview");
	PreviewLabel->SetPosition(m_UIWindow->getSize().x / 2, m_UIWindow->getSize().y / 4);

	m_SaveMenuButtonList[0] = Save;
	m_SaveMenuButtonList[1] = Load;
	m_SaveMenuButtonList[2] = PreviewLabel;
}

/// <summary>
/// Saves The Current Artwork To A Specified File Location.
/// </summary>
void CPopOutMenu::Save()
{
	sf::RenderTexture m_RenderTexture;
	m_RenderTexture.create(m_Canvas->m_Size.x, m_Canvas->m_Size.y);

	sf::View CanvasView = sf::View(sf::FloatRect(0.0f, 0.0f, m_Canvas->m_Size.x, m_Canvas->m_Size.y));
	CanvasView.setCenter(m_Canvas->m_Canvas.getPosition());
	m_RenderTexture.setView(CanvasView);

	m_RenderTexture.draw(m_Canvas->m_Canvas);

	for (sf::CircleShape& stroke : m_Shape->PaintedShapeList)
	{
		m_RenderTexture.draw(stroke);
		sf::Vector2f worldPosC = m_RenderWindow->mapPixelToCoords(sf::Vector2i(stroke.getPosition()));
	}
	for (sf::VertexArray& line : m_Shape->PaintedLineList)
	{
		m_RenderTexture.draw(line);
		sf::Vector2f worldPosD = m_RenderWindow->mapPixelToCoords(sf::Vector2i(line[0].position));
		sf::Vector2f worldPosE = m_RenderWindow->mapPixelToCoords(sf::Vector2i(line[1].position));
	}
	for (const sf::CircleShape& stroke : m_Brush->PaintedBrushList)
	{
		m_RenderTexture.draw(stroke);
		sf::Vector2f worldPosC = m_RenderWindow->mapPixelToCoords(sf::Vector2i(stroke.getPosition()));
	}

	m_RenderTexture.display();

	if (m_RenderTexture.getTexture().copyToImage().saveToFile("Images/Test.png"))
	{
		std::cout << "TEST.png Saved" << std::endl;
	}
	/*m_RenderWindow->capture();*/
}

/// <summary>
/// Shapes Menu Bool Button Check.
/// </summary>
void CPopOutMenu::ShapesMenuFillCheck()
{
	if (m_bShapeFillColour)
	{
		m_Shape->SetActiveColour(tempColour);
		m_bCustShapePreview.setFillColor(m_Shape->m_Colour);
		/*m_Shape->m_Stroke->setFillColor(m_Shape->m_Colour);*/
		m_Shape->m_PreviewStroke.setFillColor(m_Shape->m_Colour);
		m_Shape->m_PreviewStroke.setOutlineColor(m_Shape->m_Colour);
		m_bCustShapePreview.setOutlineColor(m_Shape->m_Colour);
		/*m_Shape->m_Stroke->setOutlineColor(m_Shape->m_Colour);*/
		m_Shape->m_OutlineColour = m_Shape->m_Colour;
	}
	else if (m_bShapeFillColour == false)
	{
		m_Shape->SetActiveColour(tempColour);
		m_bCustShapePreview.setFillColor(sf::Color::Transparent);
		/*m_Shape->m_Stroke->setFillColor(sf::Color::Transparent);*/
		m_Shape->m_PreviewStroke.setFillColor(sf::Color::Transparent);
		m_bCustShapePreview.setOutlineColor(m_Shape->m_Colour);
		m_Shape->m_PreviewStroke.setOutlineColor(m_Shape->m_OutlineColour);
		m_Shape->m_OutlineColour = m_Shape->m_Colour;
		m_Shape->m_Colour = sf::Color::Transparent;
		/*m_Shape->m_Stroke->setOutlineColor(m_Shape->m_Colour);*/

	}
}
