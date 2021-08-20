#pragma once
#include "CCanvas.h"
#include <list>
class CShapes
{
public:
	enum SHAPETYPE
	{
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
	

	void Render();
	void Update();
	void PaintShape();
	void SetMousePosition(sf::Vector2f Position);
	sf::Vector2f GetMousePosition();

	void SetActiveColour(sf::Color _Color);

	void Undo();

	sf::CircleShape* m_Stroke;

	int m_BushSize;
	int m_Rotation;
	int m_SideCount;

	bool m_bCreateShape;

	sf::Color m_Colour;

private:
	sf::RenderWindow* m_RenderWindow;
	sf::Vector2f m_vMousePosition;
	CCanvas* m_Canvas;
};

