#include "pch.h"
#include "scoreRecord.h"


scoreRecord::scoreRecord()
{
	nameTexture.loadFromFile("Images/name.png");
	nameSprite.setTexture(nameTexture);
	nameSprite.setOrigin(sf::Vector2f(nameTexture.getSize().x*0.5f, nameTexture.getSize().y*0.5f));
	nameSprite.setPosition(sf::Vector2f(WIDTH*0.5f,HEIGHT*0.5f));
	nameEntered.setFont(Game::font);
	nameEntered.setPosition(sf::Vector2f(nameSprite.getPosition()-sf::Vector2f(nameTexture.getSize().x*0.5f-10.0f,0.0f)));
	flag = 0;
}

void scoreRecord::Draw(sf::RenderWindow& window)
{
	Death::Draw(window);
	window.draw(nameSprite);
	window.draw(nameEntered);
}
int scoreRecord::Update()
{
	if (Game::event.type == sf::Event::TextEntered && flag==0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			return 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			name.pop_back();
		}
		else
		name += static_cast<char>(Game::event.text.unicode);
		flag = 1;
	}
	else if (Game::event.type == sf::Event::KeyReleased)
	{
		flag = 0;
	}
	nameEntered.setString(name);
	return 0;
}

scoreRecord::~scoreRecord()
{
}
