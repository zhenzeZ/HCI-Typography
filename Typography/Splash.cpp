#include "Splash.h"
#include <iostream>

Splash::Splash(Game& game, sf::Font font) :
	m_game(&game),
	m_font(font)
{
	if (!m_texture.loadFromFile("./ASSETS/IMAGES/index.jpg"))
	{
		std::string s("Error loading image");
		throw std::exception(s.c_str());
	} // loading image check

	m_text.setFont(m_font);
	m_text.setPosition(400, 240);
	m_text.setFillColor(sf::Color::Black);

	// set image states
	for (int i = 0; i < 100; i++)
	{
		m_spritePieces[i].setTexture(m_texture); // give texture image
		display_Small_Pieces_Check[i] = false; 

		int row = i / 10;
		int col = i % 10;
		sf::IntRect imageint(80 * row, 48 * col, 80, 48); // give texture 1/100 size of image
		m_spritePieces[i].setTextureRect(imageint); // set the image rect
		m_spritePieces[i].setPosition(80 * row, 48 * col); // set position 
	}

	for (int i = 0; i < 4; i++)
	{
		m_spriteBigPieces[i].setTexture(m_texture); // give texture image
		big_Pieces_Scale[i] = 1.0f;
		display_big_Pieces_Check[i] = false;

		int row = i / 2;
		int col = i % 2;
		sf::IntRect imageint(400 * row, 240 * col, 400, 240); // set rect of image
		m_spriteBigPieces[i].setOrigin(200, 120);
		m_spriteBigPieces[i].setTextureRect(imageint);
		m_spriteBigPieces[i].setPosition(400 * row + 200, 240 * col + 120); 
		m_spriteBigPieces[i].setScale(big_Pieces_Scale[i], big_Pieces_Scale[i]); // set scale
	}

}

Splash::~Splash()
{
	std::cout << "destructing Splash" << std::endl;
}

/// <summary>
/// Check time
/// </summary>
/// <param name="dt"></param>
void Splash::update(double t)
{
	if (phase == 1)
	{
		timer += t;
		if (timer >= 1.0f)
		{
			phaseOne();
		}
	}
	else if (phase == 2)
	{
		phaseTwo(t);
	}
}

/// <summary>
/// after 1 sec draw 1/100 image on screen until all 
/// </summary>
void Splash::phaseOne()
{
	int randomNum = std::rand() % 100; // get a random number

	while (display_Small_Pieces_Check[randomNum]) // check is random number appear before
	{
		randomNum = std::rand() % 100; // if appeared, get a new random number
	}

	display_Small_Pieces_Check[randomNum] = true; // display the random pieces on screen
	
	counter += 1; // count how many pieces appear

	// when all pieces appear move to next phase
	if (counter >= 100)
	{
		phase = 2;

		for (int i = 0; i < 100; i++)
		{
			display_Small_Pieces_Check[i] = false;
		}

		for (int i = 0; i < 4; i++)
		{
			display_big_Pieces_Check[i] = true;
		}

		m_text.setString("Press any key to go");
		timer = 0;
	}
}

/// <summary>
/// after key pressed,every 1 sec let a 1/4 image getting smaller until disappear
/// <param name="t"></param>
void Splash::phaseTwo(double t)
{

	if (keyPressed) // when any key pressed, start count
	{
		timer += t;
	}

	// every 1 sec let a 1/4 image disappear, when all image disappear turn to Credit
	if (timer >= 1 && timer < 2)
	{
		big_Pieces_Scale[0] = 1 - (timer - 1); // image size follo the time
		m_spriteBigPieces[0].rotate(4);
	}
	else if (timer >= 2 && timer < 3)
	{
		big_Pieces_Scale[1] = 1 - (timer - 2);
		m_spriteBigPieces[1].rotate(4);
	}
	else if (timer >= 3 && timer < 4)
	{
		big_Pieces_Scale[2] = 1 - (timer - 3);
		m_spriteBigPieces[2].rotate(4);
	}
	else if (timer >= 4 && timer < 5)
	{
		big_Pieces_Scale[3] = 1 - (timer - 4);
		m_spriteBigPieces[3].rotate(4);
	}
	else if (timer >= 5)
	{
		m_game->setGameState(States::Credit);
	}

	// key press check
	for (int index = sf::Keyboard::A; index <= 65; index++)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(index)))
		{
			keyPressed = true;
			m_text.setString("");
		}
	}

	// set the images scale
	for (int i = 0; i < 4; i++)
	{
		m_spriteBigPieces[i].setScale(big_Pieces_Scale[i], big_Pieces_Scale[i]);
	}
}

/// <summary>
/// draw the text and texture on window
/// </summary>
/// <param name="window"></param>
void Splash::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);

	for (int i = 0; i < 100; i++)
	{
		if (display_Small_Pieces_Check[i])
		{
			window.draw(m_spritePieces[i]);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (display_big_Pieces_Check[i])
		{
			window.draw(m_spriteBigPieces[i]);
		}
	}

	window.draw(m_text);

	window.display();
}