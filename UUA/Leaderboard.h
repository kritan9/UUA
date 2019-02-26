#pragma once
#include "pch.h"
#include "Game.h"

class Leaderboard
{
	std::string names[5];
	int scores[5];
	sf::Text text[5];
	int totalCoin;
	float offsetX, offsetY;
	Marshmellow marsh;
	sf::Texture t;
	sf::Sprite menuBar;
	sf::Texture tx;
	sf::Sprite txt;
	sf::Texture opts[2];
	sf::Sprite options;

public:
	Leaderboard();
	void Store();
	int check(int);
	void record(std::string a, int sc);
	void Draw(sf::RenderWindow&);
	void Update();
	~Leaderboard();
};

