#include "CPopOutMenu.h"

CPopOutMenu::CPopOutMenu(sf::RenderWindow* _RenderWindow)
{
	m_BackGround = sf::RectangleShape(sf::Vector2f(320, 720));
	m_BrushBackGround = sf::RectangleShape(sf::Vector2f(300, 640));
	m_CustomBrushBG = sf::RectangleShape(sf::Vector2f(280, 305));
	m_bCustBrushPreview = sf::CircleShape(80);

	m_BrushBackGround.setFillColor(sf::Color(204, 204, 204)); // Grey
	m_CustomBrushBG.setFillColor(sf::Color(190, 190, 190)); // Darker Grey
	m_bCustBrushPreview.setFillColor(sf::Color(209, 28, 255)); // Purple

	m_CustomBrushBG.setOrigin(m_CustomBrushBG.getGlobalBounds().width / 2, m_CustomBrushBG.getGlobalBounds().height / 2);
	m_bCustBrushPreview.setOrigin(m_bCustBrushPreview.getGlobalBounds().width / 2, m_bCustBrushPreview.getGlobalBounds().height / 2);

	m_BrushBackGround.setPosition(m_BrushBackGround.getSize().x / 30, m_BrushBackGround.getSize().y / 9);
	m_CustomBrushBG.setPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.175);
	m_bCustBrushPreview.setPosition(m_BrushBackGround.getSize().x / 2 + 10, 5 + m_BrushBackGround.getSize().y / 1.075);

	m_BrushButtonList[0] = {};
	m_InputList[0] = {};
	m_Canvas = nullptr;
	m_Brush = nullptr;
	m_RenderWindow = _RenderWindow;
	m_UIWindow = new sf::RenderWindow(sf::VideoMode(320, 720), "Tools", (sf::Style::Titlebar));
	m_UIWindow->setFramerateLimit((unsigned)120);
	
	InitColourDialogue();
}

CPopOutMenu::~CPopOutMenu()
{
	// CleanUp
	for (int i = 0; i < 10; i++)
	{
		delete m_BrushButtonList[i];
		m_BrushButtonList[i] = nullptr;
	}

	for (int i = 0; i < 1; i++)
	{
		delete m_InputList[i];
		m_InputList[i] = nullptr;
	}
	delete m_Canvas;
	delete m_Brush;
	
	m_UIWindow = nullptr;
	m_Brush = nullptr;
	m_Canvas = nullptr;
	
	m_RenderWindow = nullptr;
}

void CPopOutMenu::Start()
{
	m_Canvas = new CCanvas(m_RenderWindow, sf::Vector2f(100.0f, 100.0f));
	m_Brush = new CBrush(m_RenderWindow, m_Canvas);
	m_Brush->m_BushSize = 4;
	m_Brush->m_SideCount = 100;
	m_Brush->m_Rotation = 0.0f;
	m_Brush->m_BrushType = m_Brush->BRUSHTYPE::DEFAULT;

	CreateTabMenuButtons();
	CreateBrushButtons();
	CustomBrushButtons();

	m_bBrushMenu = false;
	m_bCustomBrush = false;
	Render();
}

void CPopOutMenu::Update()
{
	sf::Event UIEvent;
	while (m_UIWindow->pollEvent(UIEvent))
	{
		std::cout << m_BrushButtonList[2]->Sprite.getPosition().x<< std::endl;
		std::cout << m_BrushButtonList[2]->Sprite.getPosition().y << std::endl;
		/*std::cout << m_ButtonList[0]->GetMousePosition().x << std::endl;
		std::cout << m_ButtonList[0]->GetMousePosition().y << std::endl;*/
		if (UIEvent.type == sf::Event::MouseButtonPressed)
		{
			if (m_BrushButtonList[0]->bIsinBounds(m_BrushButtonList[0]->GetMousePosition()))
			{
				m_bBrushMenu = !m_bBrushMenu;
				
			}
			if (m_BrushButtonList[1]->bIsinBounds(m_BrushButtonList[1]->GetMousePosition()))
			{
				OpenColourDialogue();
				
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
		}


		if (m_bBrushMenu && m_InputList[0]->bIsinBounds(m_InputList[0]->GetMousePosition()))
		{
			InputButtonUpdate(UIEvent, 0);
		}
		else if (m_bBrushMenu && m_bCustomBrush && m_InputList[1]->bIsinBounds(m_InputList[1]->GetMousePosition()))
		{
			InputButtonUpdate(UIEvent, 1);
		}

		if ((UIEvent.type == sf::Event::KeyPressed))
		{
			m_InputList[0]->Update();
			m_InputList[1]->Update();
			Render();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			OpenColourDialogue();
		}

		//// Object Updates
		for (int i = 0; i < 9; i++)
		{
			m_BrushButtonList[i]->Update();
			
		}

		m_InputList[0]->Update();
		m_InputList[1]->Update();
		m_bCustBrushPreview.setFillColor(m_Brush->m_Colour);
	}
}

void CPopOutMenu::InputButtonUpdate (sf::Event _event, int _index)
{

	if (_event.type == sf::Event::TextEntered && m_InputList[_index]->m_Label.size() < 6 && isdigit(_event.text.unicode))
	{

		m_InputList[_index]->m_Label += _event.text.unicode;
		if (_index == 0)
		{
			m_Brush->m_BushSize = utils::StringUtils::parse<int>(m_InputList[_index]->m_Label);
		}
		else
		{
			m_bCustBrushPreview.setPointCount(utils::StringUtils::parse<int>(m_InputList[_index]->m_Label));
			m_Brush->m_SideCount = utils::StringUtils::parse<int>(m_InputList[_index]->m_Label);
		}
		

	}
	else if (_event.type == sf::Event::TextEntered && m_InputList[0]->m_Label.size() > 0 && _event.text.unicode == 8)
	{
		m_InputList[_index]->m_Label = m_InputList[_index]->removeLastChar(m_InputList[_index]->m_Label);
		if (m_InputList[_index]->m_Label == "")
		{
			if (_index == 0)
			{
				m_Brush->m_BushSize = 1;
			}
			else
			{
				m_bCustBrushPreview.setPointCount(100);
				m_Brush->m_SideCount = 100;
			}
			
		}
		else
		{
			if (_index == 0)
			{
				m_Brush->m_BushSize = utils::StringUtils::parse<int>(m_InputList[_index]->m_Label);
			}
			else
			{
				m_bCustBrushPreview.setPointCount(utils::StringUtils::parse<int>(m_InputList[_index]->m_Label));
				m_Brush->m_SideCount = utils::StringUtils::parse<int>(m_InputList[_index]->m_Label);
			}
			
		}
		
	}
}

void CPopOutMenu::Render()
{
	m_UIWindow->clear();
	m_UIWindow->draw(m_BackGround);
	if (m_bBrushMenu)
	{
		m_UIWindow->draw(m_BrushBackGround);
		
		if (m_bCustomBrush)
		{
			m_UIWindow->draw(m_CustomBrushBG);
			m_BrushButtonList[9]->RenderOnlyLabel();
			m_InputList[1]->Render();
			m_UIWindow->draw(m_bCustBrushPreview);
		}
	}
	
	m_BrushButtonList[0]->Render(); // brush button
	m_BrushButtonList[2]->Render(); // Canvas button
	m_BrushButtonList[3]->Render(); // Shapes button
	if (m_bBrushMenu)
	{
		

		m_BrushButtonList[1]->Render();  // colour button
		for (int i = 3; i < 8; i++)
		{
			m_BrushButtonList[i]->Render();
		}

		m_InputList[0]->Render();

		m_BrushButtonList[8]->RenderOnlyLabel();
	}
	

	/*for (int i = 0; i < 1; i++)
	{
		
	}*/
	
	m_UIWindow->display();
}

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

void CPopOutMenu::OpenColourDialogue()
{
	if (ChooseColor(&cc) == TRUE)
	{
		cr = cc.rgbResult;
		sf::Color tempColour;
		tempColour.r = GetRValue(cr);
		tempColour.g = GetGValue(cr);
		tempColour.b = GetBValue(cr);
		m_Brush->SetActiveColour(tempColour);
	}
	
	/*m_bColourIsOpen = !m_bColourIsOpen;*/
}

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

void CPopOutMenu::CreateShapeButtons()
{
	CInputField* BrushSize = new CInputField(m_UIWindow);
	BrushSize->SetPosition(m_UIWindow->getSize().x / 2 + m_UIWindow->getSize().x / 4.5, m_UIWindow->getSize().y / 6);

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

	m_InputList[0] = BrushSize;
}

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
	Brush->SetPosition(m_UIWindow->getSize().x - m_UIWindow->getSize().x / 20, m_UIWindow->getSize().y / 20); // Position

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

	m_BrushButtonList[0] = Brush;

	m_BrushButtonList[2] = Canvas;
	m_BrushButtonList[3] = Shape;
}

void CPopOutMenu::Save()
{
	
}
