#include "Board.hpp"


MiniBoard::MiniBoard(int tiles[BOARD_SIZE][BOARD_SIZE], sf::Vector2i parent) //For game-theoretic calculation
{
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int j = 0; j < BOARD_SIZE; j++)
		{
			tileValue[i][j] = tiles[i][j];
		}
	}
	cParent = parent;
	cUtility = 100000;
}

void MiniBoard::update(int val, int x, int y)
{
	if(x == -1 and y == -1)
		return;
	move(val, x, y);
	tileValue[x][y] = val;
}

void MiniBoard::move(int val, int x, int y)
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

void MiniBoard::flip(int val, int x, int y, sf::Vector2i dir)
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

int MiniBoard::valueOfMove(int val, int x, int y)
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

int MiniBoard::winState()
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

int MiniBoard::gameState()
{
	int count = 0;
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int j = 0; j < BOARD_SIZE; j++)
		{
			int bonus = tileValue[i][j];
			if((i == 0 and j == 0) or (i == 7 and j == 0) or (i == 7 and j == 7) or (i == 0 and j == 7))
				bonus *= 15;
			else if((i == 0 and j > 1 and j < 6) or (j == 0 and i > 1 and i < 6) or (i == 7 and j > 1 and j < 6) or (j == 7 and i > 1 and i < 6))
			    bonus *= 3;
			count += bonus;
		}
	}
	return count;
}

int MiniBoard::read(int x, int y)
{
	return tileValue[x][y];
}

void MiniBoard::setUtility(int utility)
{
	cUtility = utility;
}

int MiniBoard::utility()
{
	return cUtility;
}

sf::Vector2i MiniBoard::parent()
{
	return cParent;
}
