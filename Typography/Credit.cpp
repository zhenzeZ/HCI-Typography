#include "Credit.h"
#include <iostream>

Credit::Credit(Game& game, sf::Font font) :
	m_game(&game),
	m_font(font)
{

}

Credit::~Credit()
{
	std::cout << "destructing Credits" << std::endl;
}

/// check time
void Credit::update(double t)
{

	
}

/// draw the text on window
void Credit::render(sf::RenderWindow & window)
{
	
}