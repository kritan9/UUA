#pragma once
#include "pch.h"

class Marshmellow
{
	sf::Texture texture[50];
	sf::Texture loading;
	sf::Sprite Loading;
	sf::Sprite dance;
	int noOfFrames;
	float fps;
	std::string extension;
	std::string name;
	int temp;
public:
	Marshmellow(float framePs, int noOfF, std::string nam, std::string ext);
	void Update();
	void Draw(sf::RenderWindow&);
	void setScale(sf::Vector2f);
	void setPosition(sf::Vector2f);
	static std::string numToString(int);
	~Marshmellow();
};

