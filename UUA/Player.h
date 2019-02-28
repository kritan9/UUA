#pragma once
#include"pch.h"
#include "Game.h"

class Player :
	public GameObject
{
	float x, y, z;
	int jump;
	int yLevel;
	Point p;
	sf::Clock clock;
	float width, height;
	sf::Texture texture[4];
	sf::Sprite sprite[4];
public:
	static int playerNo;
	Player();
	Player(float Width, float Height);
	bool isPlayer() { return true; }
	void Update(float dt);
	void Reset();
	void Reset(int);
	void Draw(sf::RenderWindow&);
	sf::Vector3f position3d();
	sf::Vector3f size();
	~Player();
};

