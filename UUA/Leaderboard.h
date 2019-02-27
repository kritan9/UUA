#pragma once
#include "pch.h"
#include "Game.h"
struct scorelist
{
	std::string names[5];
	int scores[5];
};
class Leaderboard
{
	sf::Text text[5];
	scorelist scorers;
	int totalCoin;
	float offsetX, offsetY;
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

