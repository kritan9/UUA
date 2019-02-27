#include "pch.h"
#include "Leaderboard.h"


Leaderboard::Leaderboard()
{
	std::fstream scoreFile("gameData.bin", std::ios::in | std::ios::binary);
	scoreFile.read(reinterpret_cast<char*>(&scorers), sizeof(scorelist));
	scoreFile.close();
	offsetX = 60.0f; offsetY = 100.0f;
	t.loadFromFile("Images/x.png");
	menuBar.setTexture(t);
	menuBar.setPosition(0.5f*(WIDTH - menuBar.getTextureRect().width), 0.5f*(HEIGHT - menuBar.getTextureRect().height));
	tx.loadFromFile("Images/text4.png");
	txt.setTexture(tx);
	txt.setPosition(menuBar.getPosition());
	opts[0].loadFromFile("Images/Button.png");
	opts[1].loadFromFile("Images/Button2.png");
	options.setTexture(opts[0]);
	options.setPosition(menuBar.getPosition() + sf::Vector2f(offsetX, offsetY + 100.0f * 3));

	for (int i = 0; i < 5; i++)
	{
		text[i].setFont(Game::font); 
		text[i].setString(scorers.names[i] +":"+ Marshmellow::numToString(scorers.scores[i]));
		text[i].setPosition(menuBar.getPosition() + sf::Vector2f(offsetX, offsetY-30.0f + 60.0f*i));
	}

	
}

void Leaderboard::Draw(sf::RenderWindow& window)
{
	window.draw(menuBar);
	window.draw(options);
	window.draw(txt);
	for (int i = 0; i < 5; i++) window.draw(text[i]);
}

void Leaderboard::Update()
{
	static int mouseFlag = 0;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseFlag == 0)
	{
		if (Mouse::Intersect(options.getPosition().x, options.getPosition().y, (float)options.getTextureRect().width, (float)options.getTextureRect().height))
		{
			options.setTexture(opts[1]);
			mouseFlag = 1;
		}
	}

	if (Game::event.type == sf::Event::MouseButtonReleased && mouseFlag != 0)
	{
			if (Mouse::Intersect(options.getPosition().x, options.getPosition().y, (float)options.getTextureRect().width, (float)options.getTextureRect().height))
			{
				Game::gameState = Game::Menu;
			}
			options.setTexture(opts[0]);
			mouseFlag = 0;
	}
}


void Leaderboard::Store()
{
	std::fstream scoreFile("gameData.bin", std::ios::out | std::ios::binary);
	scoreFile.write(reinterpret_cast<char*>(&scorers), sizeof(scorelist));
	scoreFile.close();
	for (int i = 0; i < 5; i++)
	{
		text[i].setString(scorers.names[i] + " : " + Marshmellow::numToString(scorers.scores[i]));
	}
}

int Leaderboard::check(int s)
{
	for (int i = 0; i < 5; i++)
	{
		if (s > scorers.scores[i]) return 1;
	}
	return 0;
}

void Leaderboard::record(std::string a, int sc)
{
	int temp=0;
	std::string tem;
	for (int i = 0; i < 5; i++)
	{
		if (i == 4)
		{
			scorers.scores[i] = sc; scorers.names[i] = a;
			break;
		}
		if (sc >= scorers.scores[i])
		{
			temp = scorers.scores[i]; tem = scorers.names[i];
			scorers.scores[i] = sc;   scorers.names[i] = a;
			sc = temp;			a = tem;
		}
	}
}

Leaderboard::~Leaderboard()
{
}
