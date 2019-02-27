#pragma once
#include "Marshmellow.h"
#include "Game.h"
class Marshmellow;

class Menu
{
	sf::Texture t;
	sf::Texture tx;
	sf::Sprite txt;
	sf::Sprite menuBar;
	sf::Texture opts[2];
	sf::Sprite options[4];
	float offsetX, offsetY;
public:
	Menu();
	void Draw(sf::RenderWindow&);
	void Update();
	~Menu();
};

