//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CShapes.h
// Description : CShapes Header file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

#pragma once
#pragma warning (disable : 26812) // SILENCE MINION
#pragma warning (disable : 6255) // SILENCE MINION
#pragma warning (disable : 6387) // SILENCE MINION

// Non-Local Includes
#include <list>
#include <math.h>

// Local Includes
#include "CCanvas.h"

class CShapes
{
public:
	enum SHAPETYPE
	{
		LINE,
		CIRCLE,
		TRIANGLE,
		SQUARE,
		CUSTOM,
		SPRITE,
		DEFAULT
	};

	SHAPETYPE m_ShapeType;

	std::list<sf::CircleShape> PaintedShapeList;

	std::list<sf::VertexArray> PaintedLineList;

	sf::VertexArray LineVertexArray;

	CShapes(sf::RenderWindow* _renderWindow, CCanvas* _canvas);
	~CShapes();

	void Render();
	void Update();

	void PaintShape();
	void SetRectangle(sf::Vector2f& _startPos, sf::Vector2f& _mousePos, sf::RectangleShape& _rec);
	void LetGoOfShape();

	void SetMousePosition(sf::Vector2f _position);
	sf::Vector2f GetMousePosition();

	void SetActiveColour(sf::Color _color);

	void Undo();

	sf::CircleShape* m_Stroke;

	sf::RectangleShape m_PreviewStrokeBounds;
	sf::CircleShape m_PreviewStroke;
	sf::VertexArray m_PreviewLine;

	int m_ShapeSize;
	int m_Rotation;
	int m_SideCount;
	int m_OutlineThickness;

	bool m_bCreateShape;
	bool m_bShapeIsRect;
	bool m_bCreatePreviewShape;

	sf::Color m_Colour;
	sf::Color m_OutlineColour;

private:
	sf::RenderWindow* m_RenderWindow;

	sf::Vector2f m_vMousePosition;
	sf::Vector2f m_vMouseStart;

	CCanvas* m_Canvas;
};

