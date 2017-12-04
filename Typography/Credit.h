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

	sf::Font m_font;
	
};

#endif CREDITS // !Credits