#include "AI.hpp"

AI::AI()
{
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int j = 0; j < BOARD_SIZE; j++)
		{
			tileValue[i][j] = 0;
		}
	}
	plyDepth = 1;
}

void AI::setDifficulty(int difficulty)
{
	switch(difficulty)
	{
		case 0:
			plyDepth = 2;
			break;
		case 1:
			plyDepth = 3;
			break;
		case 2:
			plyDepth = 7;
			break;
		default:
			plyDepth = difficulty;
	}
}

void AI::readBoard(Board* board)
{
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int j = 0; j < BOARD_SIZE; j++)
		{
			tileValue[i][j] = board->read(i, j);
		}
	}
}

void AI::readBoard(MiniBoard board)
{
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int j = 0; j < BOARD_SIZE; j++)
		{
			tileValue[i][j] = board.read(i, j);
		}
	}
}

sf::Vector2i AI::update(Board* board)
{
	readBoard(board);
	plies.clear();
	moves.clear();
	plies.push_back(std::vector<MiniBoard>());
	plies[0].push_back(MiniBoard(tileValue, sf::Vector2i(0, 0)));
	for(int i = 1; i < plyDepth; i++)
	{
		plies.push_back(std::vector<MiniBoard>());
		for(int j = 0; j < plies[i - 1].size(); j++)
		{
			addStates(i, j, plies[i - 1][j]);
		}
	}

	rankTree();
	for(int i = 0; i < plies.size(); i++)
	{
		if(i == plies.size() - 1)
		{
			//std::cout << plies[i].size() << " Moves evaluated \n";
			break;
		}
		else if(plies[i].size() == 0)
		{
			//std::cout << plies[i - 1].size() << "Moves evaluated \n";
			break;
		}
	}
	
	int currentBest = 1000000;
	std::vector<sf::Vector2i> bestMoves;
	for(int j = 0; j < plies[1].size(); j++)
	{
		if(plies[1][j].utility() < currentBest)
		{
			currentBest = plies[1][j].utility();
			bestMoves.clear();
			bestMoves.push_back(moves[j]);
		}else if(plies[1][j].utility() == currentBest)
		{
			bestMoves.push_back(moves[j]);
		}
	}
	if(bestMoves.size() > 0)
		return bestMoves[rand()%bestMoves.size()];
	else
		return sf::Vector2i(-1, -1);
}

void AI::addStates(int ply, int position, MiniBoard board)
{
	readBoard(board);
	for(int x = 0; x < BOARD_SIZE; x++)
	{
		for(int y = 0; y < BOARD_SIZE; y++)
		{
			if(ply%2 == 1)
				if(board.valueOfMove(-1, x, y) < 0)
				{
					int newTiles[BOARD_SIZE][BOARD_SIZE];
					memcpy(newTiles, tileValue, sizeof(tileValue));
					plies[ply].push_back(MiniBoard(newTiles, sf::Vector2i(ply - 1, position)));
					plies[ply][plies[ply].size() - 1].update(-1, x, y);
					if(ply == 1)
						moves.push_back(sf::Vector2i(x, y));
				}
			if(ply%2 == 0)
				if(board.valueOfMove(1, x, y) > 0)
				{
					int newTiles[BOARD_SIZE][BOARD_SIZE];
					memcpy(newTiles, tileValue, sizeof(tileValue));
					plies[ply].push_back(MiniBoard(newTiles, sf::Vector2i(ply - 1, position)));
					plies[ply][plies[ply].size() - 1].update(1, x, y);
				}
		}
	}
}

void AI::rankTree()
{
	int end = plies.size() - 1;
	for(int i = 1; i < plies.size(); i++)
	{
		if(plies[i].size() == 0)
		{
			end = i - 1;
			break;
		}
	}
	for(int j = 0; j < plies[end].size(); j++)
	{
		plies[end][j].setUtility(plies[end][j].gameState());
	}
	for(int i = plies.size() - 1; i > 0; i--)
	{
		for(int j = 0; j < plies[i].size(); j++)
		{
			sf::Vector2i p = plies[i][j].parent();
			if(i%2 == 1)
				if(plies[i][j].utility() < plies[p.x][p.y].utility() or plies[p.x][p.y].utility() == 100000)
				{
					plies[p.x][p.y].setUtility(plies[i][j].utility());
				}
			if(i%2 == 0)
				if(plies[i][j].utility() > plies[p.x][p.y].utility() or plies[p.x][p.y].utility() == 100000)
				{
					plies[p.x][p.y].setUtility(plies[i][j].utility());
				}
		}
	}
}
