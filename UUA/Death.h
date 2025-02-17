#pragma once
#include "pch.h"
#include "Marshmellow.h"


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
	sf::Texture opts[2];
	sf::Sprite options[3];
	sf::Text text1;
	sf::Text text2;
	float offsetX, offsetY;
public:
	Death();
	sf::Sprite deathBar;
	void Draw(sf::RenderWindow&);
	void Update();
};

