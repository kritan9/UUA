#include "pch.h"
#include"Game.h"
#include "Marshmellow.h"


Marshmellow::Marshmellow()
{
	for (int i = 0; i < 50; i++)
	{
		if (i < 9)texture[i].loadFromFile("Images/v/v 0" + numToString(i + 1) + ".jpg");
		else texture[i].loadFromFile("Images/v/v " + numToString(i + 1) + ".jpg");
	}
	dance.setScale(sf::Vector2f((float)WIDTH/ texture[0].getSize().x,(float)HEIGHT/ texture[0].getSize().y));
}

std::string Marshmellow::numToString(int a)
{
	std::stringstream ss;
	ss << a;
	return ss.str();
}

void Marshmellow::Update()
{
	static int temp = 0;
	if (temp == 0) dance.setTexture(texture[0]);
	if (int(Game::clockTotal.getElapsedTime().asSeconds() * 5) % 50 != temp)
	{
		if (temp == 49) temp = -1;
		dance.setTexture(texture[++temp]);

	}
}
void Marshmellow::Draw(sf::RenderWindow &window)
{
	window.draw(dance);
}

Marshmellow::~Marshmellow()
{
}
