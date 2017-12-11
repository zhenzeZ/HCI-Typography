#pragma once

#ifndef CREDITS
#define CREDITS
#include <SFML\Graphics.hpp>
#include <fstream>
#include <sstream>
#include <list>
#include "Game.h"

class Game;

class Credit
{
public:
	Credit(Game& game, sf::Font font);
	~Credit();

	void update(double t);
	void render(sf::RenderWindow& window);

private:
	Game *m_game;

	void getText();

	int index = 0;
	float timer = 0;
	char spaceCheck;

	sf::Font m_font;
	sf::Text m_textMessage[10];
	bool displayText[10];
	int textColor[10];

	std::string word;
	std::ifstream file;
	std::list<sf::Text> textList;
};

#endif CREDITS // !Credits