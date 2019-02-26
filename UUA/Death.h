#pragma once
#include "pch.h"
#include "Marshmellow.h"
#include "Game.h"

namespace Mouse
{
	bool Intersect(float,float,float, float);
}

class Death
{
	sf::Texture t;
	sf::Texture tx;
	sf::Texture over;
	sf::Sprite gOver;
	sf::Sprite txt;
	sf::Sprite deathBar;
	sf::Texture opts[2];
	sf::Sprite options[3];
	float offsetX, offsetY;
	Marshmellow marsh;
public:
	Death();
	void Draw(sf::RenderWindow&);
	void Update();
};

