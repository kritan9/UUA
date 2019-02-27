#include"pch.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "Path.h"
#include "Player.h"
#include "Coin.h"
#include "Obstacle.h"

Game::GameState Game::gameState = Game::Menu;
sf::RenderWindow Game::window;
sf::Clock Game::clock;
sf::Clock Game::clockTotal;
GameObjectManager Game::gameObjectManager;
Player player(150.0f, 150.0f);
sf::Event Game::event;
int Game::level = 1;
float Game::yLevel = 150.0f;
float Game::spawnTime = 300.0f / GameObject::velocity;
int Game::score = 0;
int Game::coinCount = 0;
sf::Sound Game::coin;
sf::Sound Game::death;
sf::SoundBuffer coinBuffer;
sf::SoundBuffer deathBuffer;
sf::Font Game::font;
sf::Text text1,text2,text3;
Death Game::d;
Menu Game::m;
Marshmellow marsh(5.0f,50,"Images/v/v ",".jpg");
Marshmellow backgrnd(10.0f, 19, "Images/background/dskajd ", " copy.png");
Leaderboard Game::leadBoard;
CharacterMenu Game::cm;
std::string audioFiles[]={ "Sounds/menuLoop.ogg","Sounds/StereoMadness.ogg","Sounds/TimeMachine.ogg","Sounds/TheoryOfEverything.ogg","Sounds/Jumper.ogg","Sounds/HexagonForce.ogg","Sounds/GeometricalDominator.ogg","Sounds/Electroman.ogg","Sounds/Electrodynamix.ogg","Sounds/DryOut.ogg","Sounds/Deadlocked.ogg","Sounds/Cycles.ogg","Sounds/Clutterfunk.ogg","Sounds/Clubstep.ogg","Sounds/CantLetGo.ogg","Sounds/BlastProcessing.ogg","Sounds/BaseAfterBase.ogg","Sounds/BackOnTrack.ogg" };
int audioNum = 18; int audioPos = 0;
sf::Music bkgMusic[18];

Game::Game()
{
}

Game::~Game()
{
}

int Game::Random(int a, int b)
{
	if (a == b) return a;
	return rand() % (b - a + 1) + a;
}
void Game::Start()
{
	leadBoard.Store();
	font.loadFromFile("Images/constan.ttf");
	text1.setFont(font); text2.setFont(font);
	text3.setFont(font); 
	text2.setPosition(sf::Vector2f(WIDTH - 200.0f, 0));
	text3.setPosition(sf::Vector2f(WIDTH*0.5-100.0f, 0));
	window.create(sf::VideoMode(WIDTH, HEIGHT, 32), "Up Up And Away");
	coinBuffer.loadFromFile("Sounds/coin.wav");
	coin.setBuffer(coinBuffer);
	coin.setVolume(35);
	deathBuffer.loadFromFile("Sounds/death.wav");
	death.setBuffer(deathBuffer);
	for (int i = 0; i < audioNum; i++)
	{
		bkgMusic[i].openFromFile(audioFiles[i]);
		bkgMusic[i].setVolume(50);
	}
	audioPos = 0;
	bkgMusic[audioPos].play();
	bkgMusic[audioPos].setLoop(true);
	
	player.Reset();
	Path snakeWay(GameObject::roadLength, GameObject::roadWidth+200.0f,55);
	gameObjectManager.Add("Path", &snakeWay);
	gameObjectManager.Add("Player",&player );
	while (!IsExiting() )
	{
		GameLoop();
	}
	window.close();
}

bool Game::IsExiting()
{
	if (gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop()
{
	window.pollEvent(event);

		switch (gameState)
		{
		case Playing:
		{
			score = int(level * 2 * clockTotal.getElapsedTime().asSeconds())+coinCount*2;
			text1.setString(("Score: " + Marshmellow::numToString(score)).c_str());
			text2.setString(" Coin: " + Marshmellow::numToString(coinCount));
			text3.setString("Level: " + Marshmellow::numToString(level));
			static int q = 1; static float delT = 0.0f; static float delT2 = 0.0f;
			delT += clock.getElapsedTime().asSeconds(); delT2 += clock.getElapsedTime().asSeconds();
			if (delT2 > 3.0f)
			{
				delT2 = 0.0f;
				level++;
				if (GameObject::velocity <= 20000.0f)
				GameObject::velocity += 500.0f;
				spawnTime = 300.0f / GameObject::velocity;
			}
			if (delT >= spawnTime)
			{
				if(Random(0,10)==4)gameObjectManager.Add(" ", new Obstacle(0));
				if (q == 4)
				{	
					if (Random(0, level) != 0)
					{ 
						gameObjectManager.Add(" ", new Obstacle(Random(1, 1)));
					}
					q = 0;
				}
				else
				{
					if (Random(0, 1) == 0) gameObjectManager.Add(" ",new Coin());
					q++;
				}
				delT = 0.0f;
			}

			if (bkgMusic[audioPos].getStatus() == sf::Music::Stopped)
			{
				audioPos = Random(1, audioNum - 1);
				bkgMusic[audioPos].play();
			}

			window.clear();
			gameObjectManager.UpdateAll(clock.getElapsedTime().asSeconds());
			clock.restart();
			backgrnd.Update();
			backgrnd.Draw(window);
			gameObjectManager.DrawAll(window);
			window.draw(text1);
			window.draw(text2);
			window.draw(text3);
			window.display();

			gameObjectManager.Collision(player);
			if(gameState==Dead)
			{
				gameObjectManager.Reset();
				player.Reset();
				bkgMusic[audioPos].stop();
				audioPos = 0;
				bkgMusic[audioPos].play();
				bkgMusic[audioPos].setLoop(true);

				if (leadBoard.check(score) == 1)
				{
					gameState = RecordScore;
				}
			}
			
			if (event.type == sf::Event::Closed)
			{
				gameState = Game::Exiting;
			}
			break;
		}
		
		case Dead:
		{
			window.clear();
			d.Update();
			marsh.Update();
			marsh.Draw(window);
			d.Draw(window);
			window.display();

			if (gameState == Playing)
			{
				coinCount = 0;
				clock.restart();
				clockTotal.restart();
				bkgMusic[audioPos].setLoop(false);
				bkgMusic[audioPos].stop();
			}
			if (event.type == sf::Event::Closed)
			{
				gameState = Game::Exiting;
			}

			break;
		}
		case Menu:
		{
			window.clear();
			m.Update();
			marsh.Update();
			marsh.Draw(window);
			m.Draw(window);
			window.display();

			if (gameState == Playing)
			{
				coinCount = 0;
				bkgMusic[audioPos].setLoop(false);
				bkgMusic[audioPos].stop();
				audioPos = Random(1, audioNum - 1);
				bkgMusic[audioPos].play();
				player.Reset(CharacterMenu::pos);
				clock.restart();
				clockTotal.restart();
			}
			if (event.type == sf::Event::Closed)
			{
				gameState = Game::Exiting;
			}
			break;
		}
		case Character:
		{
			window.clear();
			cm.Update();
			marsh.Update();
			marsh.Draw(window);
			cm.Draw(window);
			window.display();

			if (event.type == sf::Event::Closed)
			{
				gameState = Game::Exiting;
			}
			break;
		}
		case HighScore:
		{
			window.clear();
			leadBoard.Update();
			marsh.Update();
			marsh.Draw(window);
			leadBoard.Draw(window);
			window.display();

			if (event.type == sf::Event::Closed)
			{
				gameState = Game::Exiting;
			}
			break;
		}
		case RecordScore:
		{
			window.clear();

			window.display();

			if (event.type == sf::Event::Closed)
			{
				gameState = Game::Exiting;
			}
			break;
		}

		}

}




