#pragma once
#include "pch.h"
class Marshmellow
{
	sf::Texture texture[50];
	sf::Sprite dance;
public:
	Marshmellow();
	void Update();
	void Draw(sf::RenderWindow&);
	static std::string numToString(int);
	~Marshmellow();
};

