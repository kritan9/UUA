#include "pch.h"
#include"Game.h"
#include "Marshmellow.h"


Marshmellow::Marshmellow(float framePs, int noOfF, std::string nam, std::string ext)
{
	temp = 0;
	name = nam; extension = ext; fps = framePs; noOfFrames = noOfF;
	//texture = new sf::Texture[noOfFrames];
	for (int i = 0; i < noOfF; i++)
	{
		if (i < 9) texture[i].loadFromFile(name +"0"+ numToString(i + 1) + extension);
		else texture[i].loadFromFile(name + numToString(i + 1) + extension);
	}
	for (int i = 0; i < noOfF; i++)
	{
		if (i < 9) texture[i].loadFromFile(name + "0" + numToString(i + 1) + extension);
		else texture[i].loadFromFile(name + numToString(i + 1) + extension);
	}
	
	dance.setScale(sf::Vector2f((float)WIDTH/ texture[0].getSize().x,(float)HEIGHT/ texture[0].getSize().y));
}

void Marshmellow::setPosition(sf::Vector2f pos)
{
	dance.setPosition(pos);
}

void Marshmellow::setScale(sf::Vector2f sc)
{
	dance.setScale(sc);
}

std::string Marshmellow::numToString(int a)
{
	std::stringstream ss;
	ss << a;
	return ss.str();
}

void Marshmellow::Update()
{
	if (temp >= noOfFrames) temp = 0;
	if (temp == 0) dance.setTexture(texture[0]);
	if (int(Game::clockTotal.getElapsedTime().asSeconds() * fps) % noOfFrames != temp)
	{
		if (temp == (noOfFrames-1)) temp = -1;
		dance.setTexture(texture[++temp]);

	}
}
void Marshmellow::Draw(sf::RenderWindow &window)
{
	window.draw(dance);
}

Marshmellow::~Marshmellow()
{
	//delete texture;
}
