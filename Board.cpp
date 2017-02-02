#include "Board.hpp"

Board::Board()
{
	boardTex.loadFromFile("Resources/Board.png");
	board.setTexture(boardTex);
	blueTex.loadFromFile("Resources/Piece Blue.png");
	bluePiece.setTexture(blueTex);
	redTex.loadFromFile("Resources/Piece Red.png");
	redPiece.setTexture(redTex);
	markTex.loadFromFile("Resources/Mark.png");
	markSprite.setTexture(markTex);
	mark = sf::Vector2i(-1, -1);
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int j = 0; j < BOARD_SIZE; j++)
		{
			tileValue[i][j] = 0;
		}
	}
	tileValue[3][3] = 1;
	tileValue[4][3] = -1;
	tileValue[3][4] = -1;
	tileValue[4][4] = 1;
}

void Board::update(int val, int x, int y, sf::RenderWindow *window)
{
	if(x == -1 and y == -1)
		return;
	move(val, x, y, window);
	if(val == -1)
		mark = sf::Vector2i(x, y);
	tileValue[x][y] = val;
}

void Board::move(int val, int x, int y, sf::RenderWindow *window)
{
	flip(val, x, y, sf::Vector2i(-1, 0), window);
	flip(val, x, y, sf::Vector2i(-1, -1), window);
	flip(val, x, y, sf::Vector2i(0, -1), window);
	flip(val, x, y, sf::Vector2i(1, -1), window);
	flip(val, x, y, sf::Vector2i(1, 0), window);
	flip(val, x, y, sf::Vector2i(1, 1), window);
	flip(val, x, y, sf::Vector2i(0, 1), window);
	flip(val, x, y, sf::Vector2i(-1, 1), window);
}

void Board::move(int val, int x, int y)
{
	flip(val, x, y, sf::Vector2i(-1, 0));
	flip(val, x, y, sf::Vector2i(-1, -1));
	flip(val, x, y, sf::Vector2i(0, -1));
	flip(val, x, y, sf::Vector2i(1, -1));
	flip(val, x, y, sf::Vector2i(1, 0));
	flip(val, x, y, sf::Vector2i(1, 1));
	flip(val, x, y, sf::Vector2i(0, 1));
	flip(val, x, y, sf::Vector2i(-1, 1));
}

void Board::flip(int val, int x, int y, sf::Vector2i dir, sf::RenderWindow *window)
{
	sf::Vector2i eye = sf::Vector2i(x, y);
	int run = false;
	do{
		eye += dir;
		if(eye.x < 0 or eye.x > BOARD_SIZE - 1 or eye.y < 0 or eye.y > BOARD_SIZE - 1)
		{
			run = false;
			break;
		}
		if(tileValue[eye.x][eye.y] == -val)
			run = true;
		else if(tileValue[eye.x][eye.y] == val and run == true)
			break;
		else if(tileValue[eye.x][eye.y] == 0)
			run = false;
	}while(run);
	if(run == true)
	{
		sf::Vector2i end = eye;
		eye = sf::Vector2i(x, y);
		for(eye; eye != end; eye+=dir)
		{
			tileValue[eye.x][eye.y] = val;
			this->draw(window);
			window->display();
			sf::sleep(sf::milliseconds(350));
		}
	}
}

void Board::flip(int val, int x, int y, sf::Vector2i dir)
{
	sf::Vector2i eye = sf::Vector2i(x, y);
	int run = false;
	do{
		eye += dir;
		if(eye.x < 0 or eye.x > BOARD_SIZE - 1 or eye.y < 0 or eye.y > BOARD_SIZE - 1)
		{
			run = false;
			break;
		}
		if(tileValue[eye.x][eye.y] == -val)
			run = true;
		else if(tileValue[eye.x][eye.y] == val and run == true)
			break;
		else if(tileValue[eye.x][eye.y] == 0)
			run = false;
	}while(run);
	if(run == true)
	{
		sf::Vector2i end = eye;
		eye = sf::Vector2i(x, y);
		for(eye; eye != end; eye+=dir)
		{
			tileValue[eye.x][eye.y] = val;
		}
	}
}

int Board::valueOfMove(int val, int x, int y)
{
	if(tileValue[x][y] != 0)
		return 0;
	int currentValue = gameState();
	int temp[BOARD_SIZE][BOARD_SIZE];
	memcpy(temp, tileValue, sizeof(temp));
	move(val, x, y);
	int newValue = gameState();
	memcpy(tileValue, temp, sizeof(tileValue));
	return newValue - currentValue;
}

int Board::winState()
{
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int j = 0; j < BOARD_SIZE; j++)
		{
			if(tileValue[i][j] == 0)
				return 0;
		}
	}
	if(gameState() > 0)
		return 1;
	if(gameState() < 0)
		return -1;
	if(gameState() == 0)
		return 2;
}

int Board::gameState()
{
	int count = 0;
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int j = 0; j < BOARD_SIZE; j++)
		{
			count += tileValue[i][j];
		}
	}
	return count;
}

void Board::draw(sf::RenderWindow* window)
{
	window->draw(board);
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int j = 0; j < BOARD_SIZE; j++)
		{
			if(tileValue[i][j] == 1)
			{
				bluePiece.setPosition(sf::Vector2f((float)i * TILE_SIZE + 3, (float)j * TILE_SIZE + 3));
				window->draw(bluePiece);
			} else if(tileValue[i][j] == -1)
			{
				redPiece.setPosition(sf::Vector2f((float)i * TILE_SIZE + 3, (float)j * TILE_SIZE + 3));
				window->draw(redPiece);
			}
			if(mark == sf::Vector2i(i, j))
			{
				markSprite.setPosition(sf::Vector2f((float)i * TILE_SIZE + 3, (float)j * TILE_SIZE + 3));
				window->draw(markSprite);
			}
		}
	}
}

int Board::read(int x, int y)
{
	return tileValue[x][y];
}
