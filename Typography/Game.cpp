#include "Game.h"
#include <iostream>

Game::Game():
	m_window(sf::VideoMode(800, 480), "Typography"),
	m_currentState(States::Credit)
{
	if (!m_font.loadFromFile("./ASSETS/FONTS/ariblk.ttf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	} // display font loading error

	m_licence = new Licence(*this, m_font);
	m_splash = new Splash(*this, m_font);
	m_credit = new Credit(*this, m_font);
}

Game::~Game()
{
	delete(m_licence);
	delete(m_splash);
	delete(m_credit);
	std::cout << "destructing game" << std::endl;
}

void Game::run()
{
	while (m_window.isOpen())
	{
		processEvents();

		timeSinceLastUpdate += m_clock.restart();

		while (timeSinceLastUpdate > timePerFrame) // reflash the window 60 times pre second
		{
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
			render();
		}
	}
}

/// <summary>
/// check the states
/// </summary>
void Game::update(sf::Time time)
{
	switch (m_currentState)
	{
	case States::Licence:
		m_licence->update(time.asSeconds());
		break;
	case States::Splash:
		m_splash->update(time.asSeconds());
		break;
	case States::Credit:
		m_credit->update(time.asSeconds());
		break;
	case States::Close:
		m_window.close();
		break;
	default:
		break;
	}
}

/// <summary>
/// display different render by currentState
/// </summary>
void Game::render()
{
	switch (m_currentState)
	{
	case States::Licence:
		m_licence->render(m_window);
		break;
	case States::Splash:
		m_splash->render(m_window);
		break;
	case States::Credit:
		m_credit->render(m_window);
		break;
	default:
		break;
	}
}

/// <summary>
/// check window close
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void Game::setGameState(States state)
{
	m_currentState = state;
}