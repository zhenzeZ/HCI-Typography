#pragma once

#ifndef SPLASH
#define SPLASH
#include <SFML\Graphics.hpp>
#include "Game.h"

class Game;

class Splash
{
public:
	Splash(Game& game, sf::Font font);
	~Splash();

	void update(double t);
	void render(sf::RenderWindow& window);

	void phaseOne();
	void phaseTwo(double t);

private:
	Game *m_game;
	
	sf::Font m_font; // for display text
	sf::Text m_text;
	sf::Texture m_texture;
	sf::Sprite m_spritePieces[100];
	sf::Sprite m_spriteBigPieces[4];

	bool display_Small_Pieces_Check[100];
	float big_Pieces_Scale[4];
	bool display_big_Pieces_Check[100];

	bool keyPressed = false;
	float timer = 0;
	int counter = 0;
	int phase = 1;
};
#endif // !SPLASH