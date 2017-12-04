#include "Licence.h"
#include <iostream>

Licence::Licence(Game& game, sf::Font font):
	m_game(&game),
	m_font(font),
	circlePosition(900, 240),
	circleScale(1)
{
	//set font and color
	m_textMessage.setFont(m_font);
	m_textMessage.setFillColor(sf::Color::Black);
	// give positon to text
	m_textMessage.setPosition(400, 200);

	m_background.setPosition(0, 0);
	m_background.setSize(sf::Vector2f(800, 480));
	m_background.setFillColor(sf::Color(1, 1, 1, 0));

	m_circleshape.setPosition(circlePosition);
	m_circleshape.setRadius(100);
	m_circleshape.setFillColor(sf::Color::White);
	m_circleshape.setOrigin(m_circleshape.getRadius(), m_circleshape.getRadius());
}

Licence::~Licence()
{
	std::cout << "destructing Licence" << std::endl;
}

void Licence::update(double t)
{ 
	m_timePassed += t; // get the time passed at licence screen

	// there are 2 different animation played on screen by time
	if (m_timePassed < 4)
	{
		phaseOne(); // the screen turn light then turn dark
	}
	else if (m_timePassed > 4)
	{
		phaseTwo();
	}

}


void Licence::phaseOne()
{
	m_textMessage.setString("Licence Screen");
	if ((m_timePassed / 2) < 1)
	{
		int i = 255 - 255 * (m_timePassed / 2);
		m_background.setFillColor(sf::Color(1, 1, 1, i)); // turn linght the screen
	}
	else
	{
		int i = 255 * (m_timePassed / 2 - 1);
		m_background.setFillColor(sf::Color(1, 1, 1, i)); // turn screen to dark
	}

}

void Licence::phaseTwo()
{
	m_textMessage.setString("Author : Zhenze");

	// when circle's y position at 241, do the first movement
	if (circleMovePhase == 1)
	{
		// move the circle from right to left
		circlePosition.x -= 4;
		if (circlePosition.x <= 300) // when circle goes to target position, move to next phase
		{
			circleMovePhase = 2;
		}
	}
	else
	{
		// move the circle from left to right
		circlePosition.x += 4;
		if (circlePosition.x >= 550) // when circle goes to target position, move to next phase
		{
			circleScale += 0.3; // increase the size of circle
		}
	}

	m_circleshape.setPosition(circlePosition);
	m_circleshape.setScale(circleScale, circleScale);

	if (circleScale >= 7)
	{
		m_game->setGameState(States::Splash); // move to Splash screen
	}
}

void Licence::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::White);

	window.draw(m_background);
	window.draw(m_circleshape);
	window.draw(m_textMessage);

	window.display();
}