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
/// PopOutMenu Constructor.
/// Takes in:	sf::RenderWindow* (Intended To Be The Main Render Window With Canvas e.t.c).
/// </summary>
CPopOutMenu::CPopOutMenu(sf::RenderWindow* _RenderWindow)
{
	// UI Essentials Creation
	m_BackGround = sf::RectangleShape(sf::Vector2f(320, 720));
	m_BrushBackGround = sf::RectangleShape(sf::Vector2f(300, 640)); // Brush Menu BG
	m_CustomBrushBG = sf::RectangleShape(sf::Vector2f(280, 305)); // Custom Brush BG
	m_SaveMenuPreviewBG = sf::RectangleShape(sf::Vector2f(280, 495)); // Save Menu Preview BG
	m_SaveMenuPreview = sf::RectangleShape(sf::Vector2f(260,260)); // Save Menu Preview Image

	m_bCustBrushPreview = sf::CircleShape(80);	// Custom Brush Preview
	m_bCustShapePreview = sf::CircleShape(70); // Custom Shape Preview

	// Set Colour
	m_BrushBackGround.setFillColor(sf::Color(204, 204, 204)); // Grey
	m_CustomBrushBG.setFillColor(sf::Color(190, 190, 190)); // Darker Grey
	m_SaveMenuPreviewBG.setFillColor(sf::Color(190, 190, 190)); // Darker Grey
	m_SaveMenuPreview.setFillColor(sf::Color::White);
	m_bCustBrushPreview.setFillColor(sf::Color(209, 28, 255)); // Purple
	m_bCustShapePreview.setFillColor(sf::Color(209, 28, 255)); // Purple
	m_bCustShapePreview.setOutlineColor(sf::Color(209, 28, 255)); // Purple

	// Set Origin's to center
	m_CustomBrushBG.setOrigin(m_CustomBrushBG.getGlobalBounds().width / 2, m_CustomBrushBG.getGlobalBounds().height / 2);
	m_SaveMenuPreviewBG.setOrigin(m_SaveMenuPreviewBG.getGlobalBounds().width / 2, m_SaveMenuPreviewBG.getGlobalBounds().height / 2);
	m_SaveMenuPreview.setOrigin(m_SaveMenuPreview.getGlobalBounds().width / 2, m_SaveMenuPreview.getGlobalBounds().height / 2);
	m_bCustBrushPreview.setOrigin(m_bCustBrushPreview.getGlobalBounds().width / 2, m_bCustBrushPreview.getGlobalBounds().height / 2);
	m_bCustShapePreview.setOrigin(m_bCustShapePreview.getGlobalBounds().width / 2, m_bCustShapePreview.getGlobalBounds().height / 2);

	// Positioning
	m_BrushBackGround.setPosition(m_BrushBackGround.getSize().x / 30, m_BrushBackGround.getSize().y / 9);
	m_CustomBrushBG.setPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.175);
	m_SaveMenuPreviewBG.setPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.425);
	m_SaveMenuPreview.setPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.425);
	m_bCustBrushPreview.setPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.075);
	m_bCustShapePreview.setPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.075);

	// Menu Initialization
	m_Canvas = nullptr;
	m_Brush = nullptr;
	m_Snip = nullptr;
	imageTex = nullptr;
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

	// CleanUp Canvas Menu Buttons
	for (int i = 0; i < 9; i++)    
	{
		delete m_CanvasButtonList[i];
		m_CanvasButtonList[i] = nullptr;
		/*std::cout << "PopedFront" << std::endl;*/
	}

	// Object and Pointer CleanUp
	delete imageTex;
	delete m_Snip;
	delete m_Canvas;
	delete m_Brush;
	delete m_Shape;
	imageTex = nullptr;
	m_Snip = nullptr;
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
	CreateCanvasMenuButtons();

	// Initialize Bools
	m_bBrushMenu = false;
	m_bSaveMenu = false;
	m_bCanvasMenu = false;
	m_bCustomBrush = false;
	m_bShapeMenu = false;
	m_bShapeFillColour = false;

	// Checks
	ShapesMenuFillCheck();

	// Render
	Render();
}

/// <summary>
/// Hover Update Check For all Input Fields. Takes in:			sf::Event
/// </summary>
/// <param name="_event"></param>
void CPopOutMenu::InputButtonHoverUpdates(sf::Event _event)
{
	// Bursh Menu Input Buttons
	if (m_bBrushMenu && m_InputList[0]->bIsinBounds(m_InputList[0]->GetMousePosition()))
	{
		InputButtonUpdate(_event, 0);
	}
	else if (m_bBrushMenu && m_bCustomBrush && m_InputList[1]->bIsinBounds(m_InputList[1]->GetMousePosition()))
	{
		InputButtonUpdate(_event, 1);
	}

	// Shape Menu Input Buttons
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
			// Tab Buttons
			if (m_BrushButtonList[0]->bIsinBounds(m_BrushButtonList[0]->GetMousePosition()))
			{
				m_bBrushMenu = !m_bBrushMenu;
				m_bShapeMenu = false;
				m_bSaveMenu = false;
				m_bCanvasMenu = false;
				std::cout << "Brush Menu Pressed" << std::endl;
			}
			if (m_BrushButtonList[1]->bIsinBounds(m_BrushButtonList[1]->GetMousePosition()) && (m_bBrushMenu || m_bShapeMenu))
			{
				OpenColourDialogue();
				
			}
			if (m_BrushButtonList[2]->bIsinBounds(m_BrushButtonList[2]->GetMousePosition()))
			{
				m_bShapeMenu = false;
				m_bBrushMenu = false;
				m_bSaveMenu = false;
				m_bCanvasMenu = !m_bCanvasMenu;
				std::cout << "Canvas Menu Pressed" << std::endl;
			}
			if (m_BrushButtonList[3]->bIsinBounds(m_BrushButtonList[3]->GetMousePosition()))
			{
				m_bShapeMenu = !m_bShapeMenu;
				m_bBrushMenu = false;
				m_bSaveMenu = false;
				m_bCanvasMenu = false;
				std::cout << "Shape Menu Pressed" << std::endl;
				InputButtonUpdate(UIEvent, 2);
			}
			if (m_BrushButtonList[10]->bIsinBounds(m_BrushButtonList[10]->GetMousePosition()))
			{
				m_bSaveMenu = !m_bSaveMenu;
				m_bShapeMenu = false;
				m_bBrushMenu = false;
				m_bCanvasMenu = false;

				CreateSnip();
				m_SaveMenuPreview.setTexture(&m_Snip->getTexture());
				std::cout << "Save Menu Pressed" << std::endl;
			}

			if (m_bBrushMenu)
			{
				// Square Brush
				if (m_BrushButtonList[4]->bIsinBounds(m_BrushButtonList[4]->GetMousePosition()))
				{
					m_Brush->m_BrushType = m_Brush->BRUSHTYPE::SQUARE;
					m_bCustomBrush = false;
				}
				// Circle Brush
				if (m_BrushButtonList[5]->bIsinBounds(m_BrushButtonList[5]->GetMousePosition()))
				{
					m_Brush->m_BrushType = m_Brush->BRUSHTYPE::CIRCLE;
					m_bCustomBrush = false;
				}
				// Triangle Brush
				if (m_BrushButtonList[6]->bIsinBounds(m_BrushButtonList[6]->GetMousePosition()))
				{
					m_Brush->m_BrushType = m_Brush->BRUSHTYPE::TRIANGLE;
					m_bCustomBrush = false;
				}
				// Custom Brush
				if (m_BrushButtonList[7]->bIsinBounds(m_BrushButtonList[7]->GetMousePosition()))
				{
					m_Brush->m_BrushType = m_Brush->BRUSHTYPE::CUSTOM;
					m_bCustomBrush = !m_bCustomBrush;
				}
			}

			if (m_bShapeMenu)
			{
				// Fill Bool Button 
				if (m_ShapeButtonList[0]->bIsinBounds(m_BrushButtonList[0]->GetMousePosition()))
				{
					m_bShapeFillColour = !m_bShapeFillColour;
					m_ShapeButtonList[0]->m_bIsPressed = !m_ShapeButtonList[0]->m_bIsPressed;
					std::cout << "Fill Button Pressed" << std::endl;

					ShapesMenuFillCheck();
				}
				// Square Shape
				if (m_ShapeButtonList[4]->bIsinBounds(m_BrushButtonList[4]->GetMousePosition()))
				{ 
					m_Shape->m_ShapeType = m_Shape->SHAPETYPE::SQUARE;
					m_Shape->m_SideCount = 4;
					m_Shape->m_Rotation = 45;
					InputButtonUpdate(UIEvent, 3);
					m_bCustomBrush = false;
				}
				// Line Shape
				if (m_ShapeButtonList[11]->bIsinBounds(m_ShapeButtonList[11]->GetMousePosition()))
				{
					m_Shape->m_ShapeType = m_Shape->SHAPETYPE::LINE;
					m_bCustomBrush = false;
				}
				// Circle Shape
				if (m_ShapeButtonList[5]->bIsinBounds(m_BrushButtonList[5]->GetMousePosition()))
				{
					m_Shape->m_ShapeType = m_Shape->SHAPETYPE::CIRCLE;
					m_Shape->m_SideCount = 100;
					m_Shape->m_Rotation = 0;
					InputButtonUpdate(UIEvent, 3);
					m_bCustomBrush = false;
				}
				// Triangle Shape
				if (m_ShapeButtonList[6]->bIsinBounds(m_BrushButtonList[6]->GetMousePosition()))
				{
					m_Shape->m_ShapeType = m_Shape->SHAPETYPE::TRIANGLE;
					m_Shape->m_SideCount = 3;
					m_Shape->m_Rotation = 0;
					InputButtonUpdate(UIEvent, 3);
					m_bCustomBrush = false;
				}
				// Custom Shape
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
				// Save Button
				if (m_SaveMenuButtonList[0]->bIsinBounds(m_SaveMenuButtonList[0]->GetMousePosition()))
				{
					SaveFileDialogue();
				}

				// Load Button
				if (m_SaveMenuButtonList[1]->bIsinBounds(m_SaveMenuButtonList[1]->GetMousePosition()))
				{
					std::cout << "Load" << std::endl;
					Load();
					m_bSaveMenu = false;
				}
			}

			if (m_bCanvasMenu)
			{
				if (m_CanvasButtonList[0]->bIsinBounds(m_CanvasButtonList[0]->GetMousePosition()))
				{
					std::cout << "TEST1" << std::endl;
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
			if (m_BrushButtonList[i] != nullptr)
			{
				m_BrushButtonList[i]->Update();
			}
		}
		for (int i = 0; i < 12; i++)
		{
			if (m_ShapeButtonList[i] != nullptr)
			{
				m_ShapeButtonList[i]->Update();
			}
		}
		for (int i = 0; i < 9 ; i++)
		{
			if (m_CanvasButtonList[i] != nullptr)
			{
				m_CanvasButtonList[i]->Update();
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
/// Performs Update Checks for specified Input Button at _index. Takes in:	sf::event , int index.
/// </summary>
/// <param name="_event"></param>
/// <param name="_index"></param>s
void CPopOutMenu::InputButtonUpdate (sf::Event _event, int _index)
{
	// Valid Input
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
	// BackSpace
	else if (_event.type == sf::Event::TextEntered && m_InputList[_index]->m_Label.size() > 0 && _event.text.unicode == 8)
	{
		m_InputList[_index]->m_Label = m_InputList[_index]->removeLastChar(m_InputList[_index]->m_Label);

		// Empty Input Check
		if (m_InputList[_index]->m_Label == "")
		{
			// Brush
			if (_index == 0)
			{
				// Brush Size
				m_Brush->m_BushSize = 1;
			}
			else if(_index == 1)
			{
				// Custom Brush Preview Side Count
				m_bCustBrushPreview.setPointCount(100);

				// Brush Side Count
				m_Brush->m_SideCount = 100;
			}

			// Shapes
			else if (_index == 2)
			{
				// Custom Shape Preview Outline Thickness
				m_bCustShapePreview.setOutlineThickness(1);

				// Shape Outline Thickness
				m_Shape->m_OutlineThickness = 1;
			}
			else if (_index == 3)
			{
				// Custom Shape Preview Side Count
				m_bCustShapePreview.setPointCount(100);

				// Shape Side Count
				m_Shape->m_SideCount = 100;
			}
		}
		else
		{
			// Brush
			if (_index == 0)
			{
				// Brush Size
				m_Brush->m_BushSize = utils::StringUtils::parse<int>(m_InputList[_index]->m_Label);
			}
			else if (_index == 1)
			{
				// Custom Brush Preview Side Count
				m_bCustBrushPreview.setPointCount(utils::StringUtils::parse<int>(m_InputList[_index]->m_Label));

				// Brush Side Count
				m_Brush->m_SideCount = utils::StringUtils::parse<int>(m_InputList[_index]->m_Label);
			}

			// Shapes
			else if (_index == 2)
			{
				// Custom Shape Preview Outline Thickness
				m_bCustShapePreview.setOutlineThickness(utils::StringUtils::parse<float>(m_InputList[_index]->m_Label));

				// Shape Outline Thickness
				m_Shape->m_OutlineThickness = utils::StringUtils::parse<float>(m_InputList[_index]->m_Label);
			}
			else if (_index == 3)
			{
				// Custom Shape Preview Side Count
				m_bCustShapePreview.setPointCount(utils::StringUtils::parse<int>(m_InputList[_index]->m_Label));

				// Shape Side Count
				m_Shape->m_SideCount = utils::StringUtils::parse<int>(m_InputList[_index]->m_Label);
			}
		}
	}

	// Invalid Input Value Re-Assignment
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

	// Canvas Menu
	if (m_bCanvasMenu)
	{
		// Sub Menu BackGround
		m_UIWindow->draw(m_BrushBackGround);

	}

	// Canvas Menu Buttons
	if (m_bCanvasMenu)
	{
		m_CanvasButtonList[0]->RenderOnlyLabel();
	}

	// Save Menu Buttons
	if (m_bSaveMenu)
	{
		m_SaveMenuButtonList[0]->Render();
		m_SaveMenuButtonList[1]->Render();
		m_SaveMenuButtonList[2]->RenderOnlyLabel();
		m_UIWindow->draw(m_SaveMenuPreview);
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
}

/// <summary>
/// Brush Menu Buttons Creation And Initialization.
/// </summary>
void CPopOutMenu::CreateBrushButtons()
{
	// Brush Size Input Field
	CInputField* BrushSize = new CInputField(m_UIWindow);
	BrushSize->SetPosition(m_UIWindow->getSize().x / 2 + m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 6);

	// Brush Size Input Label
	CButtons* BrushSizeLabel = new CButtons(m_UIWindow);
	BrushSizeLabel->SetLabel("Brush Size:");
	BrushSizeLabel->SetPosition(m_UIWindow->getSize().x / 2 - m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 6);

	// Colour Button
	CButtons* Colour = new CButtons(m_UIWindow);
	Colour->SetLabel("Colour");
	Colour->SetPosition(m_UIWindow->getSize().x / 2 + m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 4);

	// Brush Type Buttons
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

	// Array Assignment
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
	// Sides Label
	CButtons* SidesLabel = new CButtons(m_UIWindow);
	SidesLabel->SetLabel("Number Of Sides");
	SidesLabel->SetPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.55);
	m_BrushButtonList[9] = SidesLabel;

	// Sides Input Field
	CInputField* SidesInput = new CInputField(m_UIWindow);
	SidesInput->SetPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.35);
	m_InputList[1] = SidesInput;
}

/// <summary>
/// Custom Shape Menu Buttons Creation And Initialization.
/// </summary>
void CPopOutMenu::CustomShapeButtons()
{
	// Sides Label
	CButtons* SidesLabel = new CButtons(m_UIWindow);
	SidesLabel->SetLabel("Number Of Sides");
	SidesLabel->SetPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.55);
	m_ShapeButtonList[9] = SidesLabel;

	// Sides Input Field
	CInputField* SidesInputShape = new CInputField(m_UIWindow);
	SidesInputShape->SetPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.35);
	m_InputList[3] = SidesInputShape;
}

/// <summary>
/// ShapeMenu Buttons Creation And Initialization.
/// </summary>
void CPopOutMenu::CreateShapeButtons()
{
	// Outline Thickness Input Field
	CInputField* OutLineThickness = new CInputField(m_UIWindow);
	OutLineThickness->SetPosition(m_UIWindow->getSize().x / 2 + m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 6);

	// Outline Thickness Label
	CButtons* OutLineThicButton = new CButtons(m_UIWindow);
	OutLineThicButton->SetLabel("OutLine Thick:");
	OutLineThicButton->SetPosition(m_UIWindow->getSize().x / 2 - m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 6);

	// Colour Button
	CButtons* Colour = new CButtons(m_UIWindow);
	Colour->SetLabel("Colour");
	Colour->SetPosition(m_UIWindow->getSize().x / 2 + m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 4);

	// Shape Type Buttons
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
	
	// Fill Shape Bool Button Label
	CButtons* BoolLabel = new CButtons(m_UIWindow);
	BoolLabel->SetLabel("Fill");
	BoolLabel->SetPosition(m_UIWindow->getSize().x / 2 + m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 2.4);
	m_ShapeButtonList[10] = BoolLabel;

	// Fill Shape Bool Button
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

	// Array Assignment
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
	// Brush Menu Button
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

	// Canvas Menu Button
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

	// Shape Menu Button
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

	// Save Menu Button
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

	// Array Assignment
	m_BrushButtonList[0] = Brush;

	m_BrushButtonList[2] = Canvas;
	m_BrushButtonList[3] = Shape;
	m_BrushButtonList[10] = Save;
}

/// <summary>
/// Save Menu Buttons Creation And Initialization.
/// </summary>
void CPopOutMenu::CreateSaveMenuButtons()
{
	// Save Button
	CButtons* Save = new CButtons(m_UIWindow);
	Save->SetLabel("Save");
	Save->SetPosition(m_UIWindow->getSize().x / 2 - m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 6);

	// Load Button
	CButtons* Load = new CButtons(m_UIWindow);
	Load->SetLabel("Load");
	Load->SetPosition(m_UIWindow->getSize().x / 2 + m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 6);

	// Preview Image Label
	CButtons* PreviewLabel = new CButtons(m_UIWindow);
	PreviewLabel->SetLabel("Image Preview");
	PreviewLabel->SetPosition(m_UIWindow->getSize().x / 2, m_UIWindow->getSize().y / 4);

	// Array Assignment
	m_SaveMenuButtonList[0] = Save;
	m_SaveMenuButtonList[1] = Load;
	m_SaveMenuButtonList[2] = PreviewLabel;
}

/// <summary>
/// Canvas Menu Buttons Creation And Initialization.
/// </summary>
void CPopOutMenu::CreateCanvasMenuButtons()
{
	// Colour Button Label
	CButtons* ColorLabel = new CButtons(m_UIWindow);
	ColorLabel->SetLabel("BG Color:");
	ColorLabel->SetPosition(m_UIWindow->getSize().x / 2 - m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 6);

	// Array Assignment
	m_CanvasButtonList[0] = ColorLabel;
}

/// <summary>
/// Saves The Current Artwork To A Specified File Location.
/// Takes In:	std::string Adress
/// </summary>
void CPopOutMenu::Save(std::string& _fileName)
{
	CreateSnip();

	// Save Snip To File
	if (m_Snip->getTexture().copyToImage().saveToFile(_fileName))
	{
		std::cout << _fileName << " +Saved!" << std::endl;
	}
}

/// <summary>
/// Load A Specified Image From File Location.
/// </summary>
void CPopOutMenu::Load()
{
	// Object CleanUp
	delete m_Brush;
	delete m_Shape;
	
	// Object Recreation
	m_Brush = new CBrush(m_RenderWindow, m_Canvas);
	m_Shape = new CShapes(m_RenderWindow, m_Canvas);

	// Recreated Essentials Initialization
	m_Brush->m_BrushType = m_Brush->BRUSHTYPE::DEFAULT;
	m_Brush->m_BushSize = 1;
	m_Brush->m_SideCount = 100;
	m_Brush->m_Rotation = 0.0f;

	m_Shape->m_ShapeType = m_Shape->SHAPETYPE::DEFAULT;
	m_Shape->m_SideCount = 100;
	m_Shape->m_Rotation = 0.0f;

	OpenFileDialogue(m_Canvas->m_Canvas);

	// Render
	m_Canvas->Render();

	// Update
	Update();
}

/// <summary>
/// Assigns m_Snip a new sf::RenderTexture containing an image of the canvas.
/// </summary>
void CPopOutMenu::CreateSnip()
{
	// Previous Snip Cleanup
	delete m_Snip;
	m_Snip = nullptr;

	// Snip Recreation
	m_Snip = new sf::RenderTexture();
	m_Snip->create(m_Canvas->m_Size.x, m_Canvas->m_Size.y);

	// Set Render Window To Look At Canvas
	sf::View CanvasView = sf::View(sf::FloatRect(0.0f, 0.0f, m_Canvas->m_Size.x, m_Canvas->m_Size.y));
	CanvasView.setCenter(m_Canvas->m_Canvas.getPosition());
	m_Snip->setView(CanvasView);

	// Draw Canvas To Snip 
	m_Snip->draw(m_Canvas->m_Canvas);

	// Draw Brush, Shapes, e.t.c to Snip
	for (sf::CircleShape& stroke : m_Shape->PaintedShapeList)
	{
		// Shapes
		m_Snip->draw(stroke);
		sf::Vector2f worldPosC = m_RenderWindow->mapPixelToCoords(sf::Vector2i(stroke.getPosition()));
	}
	for (sf::VertexArray& line : m_Shape->PaintedLineList)
	{
		// Lines
		m_Snip->draw(line);
		sf::Vector2f worldPosD = m_RenderWindow->mapPixelToCoords(sf::Vector2i(line[0].position));
		sf::Vector2f worldPosE = m_RenderWindow->mapPixelToCoords(sf::Vector2i(line[1].position));
	}
	for (const sf::CircleShape& stroke : m_Brush->PaintedBrushList)
	{
		// Brush
		m_Snip->draw(stroke);
		sf::Vector2f worldPosC = m_RenderWindow->mapPixelToCoords(sf::Vector2i(stroke.getPosition()));
	}

	// Display
	m_Snip->display();
}

/// <summary>
/// Opens The PopUp Open File Dialogue Window.
/// Takes In:	sf::RectangleShape Adress (Canvas To Update With Image)
/// </summary>
/// <param name="_canvas"></param>
void CPopOutMenu::OpenFileDialogue(sf::RectangleShape& _canvas)
{
	IFileOpenDialog* pFileOpen;
	hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

	if (SUCCEEDED(hr))
	{
		// Show the Open dialog box.
		hr = pFileOpen->Show(NULL);

		// Get the file name from the dialog box.
		if (SUCCEEDED(hr))
		{
			IShellItem* pItem;
			hr = pFileOpen->GetResult(&pItem);
			if (SUCCEEDED(hr))
			{
				PWSTR pszFilePath;
				hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

				// Display the file name to the user.
				if (SUCCEEDED(hr))
				{
					USES_CONVERSION;

					std::string temp;

					temp = PathFindExtensionA(W2A(pszFilePath));

					std::cout << temp << std::endl;

					if (temp == ".png")
					{
						std::cout << "true" << std::endl;
						
						imageTex = new sf::Texture();

						if (!imageTex->loadFromFile(W2A(pszFilePath)))
							std::cout << "error" << std::endl;

						imageTex->loadFromFile(W2A(pszFilePath));

						//
						// Update Canvas
						//
						_canvas = sf::RectangleShape(sf::Vector2f(imageTex->getSize().x, imageTex->getSize().y));
						_canvas.setFillColor((sf::Color::White));
						_canvas.setTexture(imageTex, true);
						_canvas.setSize(sf::Vector2f(imageTex->getSize().x, imageTex->getSize().y));
						_canvas.setOrigin(_canvas.getGlobalBounds().width / 2, _canvas.getGlobalBounds().height / 2);
						_canvas.setPosition(0.0f, 0.0f);
					}

					MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
					CoTaskMemFree(pszFilePath);
				}
				pItem->Release();
			}
		}
		pFileOpen->Release();
	}
}

/// <summary>
/// Opens The PopUp Save File Dialogue Window And Proceeds To Call Save() With The Input File Path.
/// </summary>
void CPopOutMenu::SaveFileDialogue()
{
	IFileSaveDialog* pFileSave;
	hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));

	if (SUCCEEDED(hr))
	{
		// Show the Open dialog box.
		hr = pFileSave->Show(NULL);

		// Get the file name from the dialog box.
		if (SUCCEEDED(hr))
		{
			IShellItem* pItem;
			hr = pFileSave->GetResult(&pItem);
			if (SUCCEEDED(hr))
			{
				PWSTR pszFilePath;
				hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

				// Display the file name to the user.
				if (SUCCEEDED(hr))
				{
					USES_CONVERSION;

					std::string* temp = new std::string();

					*temp = PathFindFileNameA(W2A(pszFilePath));

					std::cout << *temp << std::endl;

					// Save To Specified File Path
					Save(*temp);

					MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);

					// Cleanup
					delete temp;
					temp = nullptr;
					CoTaskMemFree(pszFilePath);
				}
				pItem->Release();
			}
		}
		pFileSave->Release();
	}
}

/// <summary>
/// Shapes Menu Bool Button Check. (m_bShapeFillColour)
/// </summary>
void CPopOutMenu::ShapesMenuFillCheck()
{
	if (m_bShapeFillColour)
	{
		m_Shape->SetActiveColour(tempColour);

		m_bCustShapePreview.setFillColor(m_Shape->m_Colour);
		m_Shape->m_PreviewStroke.setFillColor(m_Shape->m_Colour);
		m_Shape->m_PreviewStroke.setOutlineColor(m_Shape->m_Colour);

		m_bCustShapePreview.setOutlineColor(m_Shape->m_Colour);

		m_Shape->m_OutlineColour = m_Shape->m_Colour;
	}
	else if (m_bShapeFillColour == false)
	{
		m_Shape->SetActiveColour(tempColour);

		m_bCustShapePreview.setFillColor(sf::Color::Transparent);
		m_Shape->m_PreviewStroke.setFillColor(sf::Color::Transparent);

		m_bCustShapePreview.setOutlineColor(m_Shape->m_Colour);

		m_Shape->m_PreviewStroke.setOutlineColor(m_Shape->m_OutlineColour);

		m_Shape->m_OutlineColour = m_Shape->m_Colour;
		m_Shape->m_Colour = sf::Color::Transparent;

	}
}
