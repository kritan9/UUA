#include "pch.h"
#include "Player.h"
#define PLAYERVELOCITY 3000.0f*RELEASE

float TimePeriod = 0.5f;
float uSpeed = 4.05f*Game::yLevel / TimePeriod;
float acc = 2 * uSpeed / TimePeriod;  
float t;
int Player::playerNo = 0;
Player::Player() {}

void Player::Reset()
{ 
	x = (WIDTH - width)*0.5f;  z = 50.0f; jump = 0; yLevel = 1; y = Game::yLevel*yLevel-50.0f;
}

void Player::Reset(int n)
{
	playerNo = n % 4;
	x = (WIDTH - width)*0.5f; z = 50.0f; jump = 0; yLevel = 1; y = Game::yLevel*yLevel - 50.0f;
}

void Player::Draw(sf::RenderWindow & renderWindow)
{
		renderWindow.draw(sprite[playerNo]);
}

Player::Player(float Width,float Height)
{
	x = (WIDTH - Width)*0.5f; y = 150.0f; z = 50.0f;
	p.setPoint(x,y,z);
	jump = 0;  yLevel = 1;
	width = Width; height = Height;
	SetPosition(p.getScreenPoint().x, p.getScreenPoint().y);
	texture[0].loadFromFile("Images/character2.png");
	texture[1].loadFromFile("Images/character.png");
	texture[2].loadFromFile("Images/thanos.png");
	texture[3].loadFromFile("Images/superman.png");

	for (int i = 0; i < 4; i++)
	{
		sprite[i].setTexture(texture[i]);
		sprite[i].setScale(sf::Vector2f(Width*p.scale / texture[i].getSize().x, p.scale* Height / texture[i].getSize().y));
	}
}


void Player::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))	x-=PLAYERVELOCITY*dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))   x+=PLAYERVELOCITY*dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && jump == 0 && /*(yLevel==2 ||*/ yLevel==1)
	{ 
		jump = 1; clock.restart(); 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && jump == 0 && /*(yLevel == 3 ||*/ yLevel == 2)
	{ 
		jump = -1;  clock.restart();
	}

	if (x < (WIDTH - GameObject::roadWidth)*0.5f) x= (WIDTH - GameObject::roadWidth)*0.5f;
	if (x > (WIDTH + GameObject::roadWidth)*0.5f - width*p.scale) x=(WIDTH + GameObject::roadWidth )*0.5f-width*p.scale;

	if (jump == 1) 
	{
		t = clock.getElapsedTime().asSeconds();
	//	y = (yLevel*Game::yLevel-50.0f) + uSpeed*t-0.5f*acc*t*t;
		y = (yLevel*Game::yLevel - 50.0f) + uSpeed * 0.5f*t;
		//if (yLevel == 2) { if (y >= ((yLevel+1)*Game::yLevel - 50.0f)) { yLevel = 3; y=yLevel*Game::yLevel - 50.0f;  jump = 0; } }
		if (yLevel == 1) { if (y >= ((yLevel + 1)*Game::yLevel - 50.0f)) { yLevel = 2; y=yLevel*Game::yLevel - 50.0f;  jump = 0; } }
	}
	if (jump == -1)
	{
		t = clock.getElapsedTime().asSeconds();
		//y = (yLevel*Game::yLevel - 50.0f) - uSpeed * t + 0.5f*acc*t*t;
		y = (yLevel*Game::yLevel - 50.0f) - uSpeed * 0.5f*t;
		if (yLevel == 2) { if (y <= ((yLevel - 1)*Game::yLevel - 50.0f)) { yLevel = 1; y=yLevel*Game::yLevel - 50.0f;  jump = 0;} }
		//if (yLevel == 3) { if (y <= ((yLevel - 1)*Game::yLevel - 50.0f)) { yLevel = 2; y=yLevel*Game::yLevel - 50.0f;  jump = 0;} }
	}
	if (y > 2/*3*/ * Game::yLevel - 50.0f)
	{
		y = 2.0f * Game::yLevel - 50.0f; yLevel = 2; jump = 0; //3.0f  3
	}
	if (y < Game::yLevel - 50.0f) 
	{
		y = 1.0f * Game::yLevel - 50.0f; yLevel = 1; jump = 0;
	}

	p.setPoint(x, y, z);
		sprite[playerNo].setRotation(-40.0f*(x + width * 0.5f) / WIDTH + 20.0f);
		sprite[playerNo].setPosition(p.getScreenPoint().x, p.getScreenPoint().y);
}

sf::Vector3f Player::position3d()
{
	if(playerNo==3) return sf::Vector3f(x + 35.0f, y, z);
	return sf::Vector3f(x+20.0f, y, z);
}

sf::Vector3f Player::size()
{
	if (playerNo == 3) return sf::Vector3f(width - 55.0f, -50.0f, -300.0f);
	return sf::Vector3f(width-40.0f, -50.0f, -300.0f);
}

Player::~Player()
{
}
