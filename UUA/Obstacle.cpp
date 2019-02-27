#include "pch.h"
#include "Obstacle.h"

float roadBeg = (WIDTH - GameObject::roadWidth)*0.5f;
class temporary
{
public:
	sf::Texture obs[10];
	temporary()
	{
		for (int i = 0; i < 10; i++)
		{
			if (i < 9) obs[i].loadFromFile("Images/dr/dr 0" + Marshmellow::numToString(i + 1) + " copy.png");
			else obs[i].loadFromFile("Images/dr/dr " + Marshmellow::numToString(i + 1) + " copy.png");
		}

	}
};
temporary xyz;

Obstacle::Obstacle(int n)
{
	obsNo = n;
	imageNo = 0;
	if (n == 0)
	{ 
		width = 300.0f; height = 100.0f; thickness = 50.0f;
		Load("Images/Obstacle.png");
	}
	if (n == 1)
	{
		width = 500.0f; height = 150.0f; thickness = 50.0f; Load("Images/dr/dr 01 copy.png");
	}
	roadX = (float)Game::Random(0, (int)(GameObject::roadWidth - thickness));
	z = GameObject::roadLength;
	if(n==0) 
		x = -600.0f;
	else
		x = roadBeg + roadX + GameObject::curveX(z); 
	y = Game::Random(1, 3)*Game::yLevel;
	p.setPoint(x, y, z);
		SetScale(width*p.Scale() / texture.getSize().x, p.Scale()* height / texture.getSize().y);
		SetPosition(p.getScreenPoint().x, p.getScreenPoint().y);
}

void Obstacle::Update(float dt)
{
	z -= velocity * dt;
	if(obsNo!=0)
		x = roadX + roadBeg + GameObject::curveX(z);
	p.setPoint(x, y, z);
	SetScale(width*p.Scale() / texture.getSize().x, p.Scale()* height / texture.getSize().y);
	sprite.setRotation(-20.0f*(x - curveX(z) + width * 0.5f) / GameObject::roadWidth + 10.0f);
	SetPosition(p.getScreenPoint().x, p.getScreenPoint().y);
	if (obsNo == 1)
	{
		if (imageNo >= 10) imageNo = 0;
		if (imageNo == 0) sprite.setTexture(xyz.obs[0]);
		if (int(Game::clockTotal.getElapsedTime().asSeconds() * 5) % 10 != imageNo)
		{
			if (imageNo == (10 - 1)) imageNo = -1;
			sprite.setTexture(xyz.obs[++imageNo]);

		}
	}
	
}

sf::Vector3f Obstacle::position3d()
{
	if (obsNo == 0)
	return sf::Vector3f(x, y, z);
}

sf::Vector3f Obstacle::size()
{
	return sf::Vector3f(width, -height, thickness);
}

bool Obstacle::destroy() {
	if (z < -10.0f) return true;
	else return false;
}

Obstacle::~Obstacle()
{
}