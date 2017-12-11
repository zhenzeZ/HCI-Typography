#include "Credit.h"
#include <iostream>

Credit::Credit(Game& game, sf::Font font) :
	m_game(&game),
	m_font(font)
{
	for (int i = 0; i < 10; i++) {
		m_textMessage[i].setFont(m_font);
		m_textMessage[i].setFillColor(sf::Color(1,1,1,0)); // set color to text

		displayText[i] = false;
		textColor[i] = 0;
	}

	file.open("./ASSETS/CREDIT/Credit.txt"); //oprn txt file 
}

Credit::~Credit()
{
	std::cout << "destructing Credits" << std::endl;
}

/// <summary>
/// display text on screen and swtich to new text
/// </summary>
/// <param name="t"></param>
void Credit::update(double t)
{
	timer += t;

	if (index < 10 && timer >= 0.5f) // read file every 0.5 sec 
	{
		getText();
		timer = 0; // reset the timer
	}

	if (file.eof() && timer >= 0.4f) // if system read the end of file, turn to close phase
	{
		m_game->setGameState(States::Close);
	}
	else if (!file.eof() && index >= 10) // if index is more than 10, reset the text states
	{
		index = 0;

		for (int i = 0; i < 10; i++)
		{
			textColor[i] = 0;
			displayText[i] = false;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (displayText[i] && textColor[i] < 255)
		{
			textColor[i]++;
			m_textMessage[i].setFillColor(sf::Color(1, 0, 0, textColor[i])); // let text appear
		}
	}

	m_textMessage[index].setPosition(50, 50 + index * 40); // set position to text
}


/// <summary>
/// read the text from file and sign to string
/// </summary>
void Credit::getText()
{
	if (file.is_open())
	{

		if (index < 10)
		{
			/*spaceCheck = file.get();

			while (spaceCheck != ' ')
			{
				word = word + spaceCheck;
				spaceCheck = file.get();
			}*/
			std::getline(file, word);

			//Getting every line of the .txt file and putting it in the 'line' string
			m_textMessage[index].setString(word);
			textList.push_back(m_textMessage[index]);

			displayText[index] = true;
			index++;
			//word = " ";
		}
	}
	else
	{
		std::string s("Error loading text ");
		throw std::exception(s.c_str());
	}
}

/// <summary>
/// draw the text on window
/// </summary>
/// <param name="window"></param>
void Credit::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);

	for (int i = 0; i < 10; i++)
	{
		window.draw(m_textMessage[i]);
	}

	window.display();
}