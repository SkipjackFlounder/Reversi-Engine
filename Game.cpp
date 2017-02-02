#include "Game.hpp"

Game::Game(int difficulty)
{
	font.loadFromFile("Resources/DroidSans.ttf");
	title.setFont(font);
	title.setCharacterSize(24);
	title.setColor(sf::Color::White);
	title.setPosition(sf::Vector2f(1010, 20));
	title.setStyle(sf::Text::Bold | sf::Text::Underlined);
	title.setString("Reversi: Human vs. AI");
	text.setFont(font);
	text.setCharacterSize(16);
	text.setColor(sf::Color::White);
	text.setPosition(sf::Vector2f(1010, 90));
	warning.setFont(font);
	warning.setCharacterSize(16);
	warning.setColor(sf::Color::White);
	warning.setPosition(sf::Vector2f(1010, 150));
	warning.setStyle(sf::Text::Bold);
	ai.setDifficulty(difficulty);
}

void Game::update(sf::RenderWindow* window)
{
	warning.setString("Right click to skip turn");
	if(board.winState() == -1)
		warning.setString("AI wins");
	else if(board.winState() == 1)
		warning.setString("Human wins");
	board.draw(window);
	/*AISkipped = true;
	humanSkipped = true;
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int j = 0; j < BOARD_SIZE; j++)
		{
			if(board.valueOfMove(-1, i, j) != 0)
				AISkipped = false;
			else if(board.valueOfMove(1, i, j) != 0)
				humanSkipped = false;
		}
	}
	if(AISkipped)
		warning.setString("AI's turn is skipped");
	else if(humanSkipped)
	{
		warning.setString("Human's turn is skipped");
		sf::sleep(sf::milliseconds(2000));
	}*/
}

void Game::handleInput(sf::RenderWindow* window, sf::View* view)
{
	sf::Vector2i mousePos = sf::Vector2i(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
	bool right = false;
	if(helper::rightMouseClicked())
		right = true;
	if((helper::leftMouseClicked() or right) and mousePos.x < 1000 and mousePos.y < 1000 and mousePos.x > 0 and mousePos.y > 0)
	{
		if(board.valueOfMove(1, mousePos.x/TILE_SIZE, mousePos.y/TILE_SIZE) != 0 or right)
		{
			if(!right)
				board.update(1,  mousePos.x/TILE_SIZE, mousePos.y/TILE_SIZE, window);

			sf::Vector2i aiMove = ai.update(&board);
			board.update(-1, aiMove.x, aiMove.y, window);
		}
		sf::sleep(sf::milliseconds(500));
		warning.setString("");
	}
}

void Game::displayText(sf::RenderWindow* window)
{
	window->draw(title);
	int state = board.gameState();
	if(state == 0)
		text.setString("The game is tied");
	else if(state > 0)
		text.setString("Human is winning by " + helper::intToString(state) + " points");
	else
		text.setString("AI is winning by " + helper::intToString(-state) + " points");
	window->draw(text);
	window->draw(warning);
}
