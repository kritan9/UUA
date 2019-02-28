#include "pch.h"
#include "Obstacle.h"

float roadBeg = (WIDTH - GameObject::roadWidth)*0.5f;
class temporary
{
public:
	sf::Texture obs[10];
	sf::Texture obs2[16];
	temporary()
	{
		for (int i = 0; i < 10; i++)
		{
			if (i < 9) obs[i].loadFromFile("Images/dr/dr 0" + Marshmellow::numToString(i + 1) + " copy.png");
			else obs[i].loadFromFile("Images/dr/dr " + Marshmellow::numToString(i + 1) + " copy.png");
		}
		for (int i = 0; i < 16; i++)
		{
			 obs2[i].loadFromFile("Images/ob/ob (" + Marshmellow::numToString(i + 1) + ").png");
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
	if (n == 1 )
	{
		width = 500.0f; height = 150.0f; thickness = 50.0f; Load("Images/dr/dr 01 copy.png");
	}
	if (n == 2)
	{
		width = 500.0f; height = 200.0f; thickness = 50.0f; Load("Images/ob/ob (1).png");
	}
	if (n == 3)
	{
		width = 259.0f; height = 224.0f; thickness = 60.0f; Load("Images/rocket.png");
	}
	if (n == 4)
	{
		width = 220.0f; height = 150.0f; thickness = 50.0f; Load("Images/goku.png");
	}
	roadX = (float)Game::Random(0, (int)(GameObject::roadWidth - thickness));
	z = GameObject::roadLength;
	if(n==0) 
		x = -600.0f;
	else
		x = roadBeg + roadX + GameObject::curveX(z); 
	
		y = Game::Random(1, 2)*Game::yLevel;

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
	if (obsNo == 2)
	{
		if (imageNo >= 16) imageNo = 0;
		if (imageNo == 0) sprite.setTexture(xyz.obs2[0]);
		if (int(Game::clockTotal.getElapsedTime().asSeconds() * 4) % 16 != imageNo)
		{
			if (imageNo == (16 - 1)) imageNo = -1;
			sprite.setTexture(xyz.obs2[++imageNo]);

		}
	}
	
}

sf::Vector3f Obstacle::position3d()
{
	if(obsNo==1 ) return sf::Vector3f(x+20.0f, y, z);
	else if (obsNo == 2) return sf::Vector3f(x + 35.0f, y, z);
	else if (obsNo == 3) return sf::Vector3f(x + 15.0f, y, z);
	else return sf::Vector3f(x , y, z);
}

sf::Vector3f Obstacle::size()
{
	if(obsNo==1 ) return sf::Vector3f(width-40.0f, -height, thickness);
	else if (obsNo == 2) return sf::Vector3f(width - 70.0f, -height, thickness);
	else if (obsNo == 3) return sf::Vector3f(width - 30.0f, -height, thickness);
	return sf::Vector3f(width, -height, thickness);
}

bool Obstacle::destroy() {
	if (z < -15.0f) return true;
	else return false;
}

Obstacle::~Obstacle()
{
}