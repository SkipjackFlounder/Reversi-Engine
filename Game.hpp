#include "AI.hpp"

class Game
{
	private:
		Board board;
		AI ai;
		bool humanSkipped;
		bool AISkipped;
		sf::Font font;
		sf::Text title, text, warning;
	public:
		Game(int);
		void update(sf::RenderWindow*);
		void handleInput(sf::RenderWindow*, sf::View*);
		void displayText(sf::RenderWindow*);
};
