#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

static sf::Vector2i WindowSize{ 1000, 1000 };
static float DeltaTime;
static float CurrentTime;
static sf::Clock MainClock{};
static bool ExitProgram;
static std::map<sf::Keyboard::Key, bool> KeyMap;
static sf::RenderWindow* RenderWindow;

static void Print(std::string_view&& _message)
{
	std::cout << _message << std::endl;
}
static void Print(int&& _int)
{
	std::cout << _int << std::endl;
}
static void Print(float&& _float)
{
	std::cout << _float << std::endl;
}
static void Print(char&& _character)
{
	std::cout << _character << std::endl;
}

static void SetDeltaTime(float&& _newValue)
{
	DeltaTime = _newValue;
}

