#include "Board.hpp"

class AI
{
	private:
		int tileValue[BOARD_SIZE][BOARD_SIZE];
		std::vector< std::vector<MiniBoard> > plies;
		std::vector<sf::Vector2i> moves;
		void addStates(int, int, MiniBoard);
		void rankTree();
		void readBoard(Board*);
		void readBoard(MiniBoard);
		int plyDepth;
	public:
		AI();
		void setDifficulty(int);
		sf::Vector2i update(Board*);
};
