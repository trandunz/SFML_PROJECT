#pragma once
#include "CCanvas.h"
#include <list>
#include <math.h> 
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

	CShapes(sf::RenderWindow* _renderWindow, CCanvas* _canvas);
	~CShapes();
	std::list<sf::CircleShape> PaintedShapeList;
	sf::VertexArray LineVertexArray;
	std::list<sf::VertexArray> PaintedLineList;
	

	void Render();
	void Update();
	void PaintShape();
	void LetGoOfShape();
	void SetMousePosition(sf::Vector2f Position);
	sf::Vector2f GetMousePosition();

	void SetActiveColour(sf::Color _Color);

	void Undo();

	sf::CircleShape* m_Stroke;
	sf::CircleShape m_PreviewStroke;
	sf::VertexArray m_PreviewLine;

	int m_ShapeSize;
	int m_Rotation;
	int m_SideCount;
	int m_OutlineThickness;

	bool m_bCreateShape;
	bool m_bCreatePreviewShape;

	sf::Color m_Colour;
	sf::Color m_OutlineColour;

private:
	sf::RenderWindow* m_RenderWindow;
	sf::Vector2f m_vMousePosition;
	CCanvas* m_Canvas;

	sf::Vector2f m_vMouseStart;
};

