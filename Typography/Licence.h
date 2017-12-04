#pragma once
#ifndef LICENCE
#define LICENCE

#include <SFML\Graphics.hpp>
#include "Game.h"

/// <summary>
/// author zhenze zhao
/// </summary>

class Game;

class Licence
{
public:
	Licence(Game& game, sf::Font font);
	~Licence();

	void update(double t);
	void render(sf::RenderWindow &window);

	void phaseOne();
	void phaseTwo();
private:
	Game *m_game;

	double m_timePassed;
	sf::Font m_font;
	sf::Text m_textMessage;
	
	sf::RectangleShape m_background;
	sf::CircleShape m_circleshape;

	int circleMovePhase = 1;
	sf::Vector2f circlePosition;
	float circleScale;
};

#endif // !LICENCE