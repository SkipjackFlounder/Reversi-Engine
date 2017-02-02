#ifndef _BOARD_HPP
#define _BOARD_HPP
#include "Hardware.hpp"
#define BOARD_SIZE 8
#define TILE_SIZE 100

class Board
{
	private:
		sf::Texture boardTex, blueTex, redTex, markTex;
		sf::Vector2i mark;
		int tileValue[BOARD_SIZE][BOARD_SIZE];
		sf::Sprite board, bluePiece, redPiece, markSprite;
		void move(int,int,int, sf::RenderWindow *);
		void move(int,int,int);
		void flip(int,int,int,sf::Vector2i, sf::RenderWindow *);
		void flip(int,int,int,sf::Vector2i);
	public:
		Board();
		void update(int,int,int, sf::RenderWindow *);
		int valueOfMove(int,int,int);
		int winState();
		int gameState();
		void draw(sf::RenderWindow*);
		int read(int,int);
		
};

class MiniBoard
{
	private:
		int tileValue[BOARD_SIZE][BOARD_SIZE];
		void move(int,int,int);
		void flip(int,int,int,sf::Vector2i);
		int cUtility;
		sf::Vector2i cParent;
	public:
		MiniBoard(int tiles[BOARD_SIZE][BOARD_SIZE], sf::Vector2i parent);
		void update(int,int,int);
		int valueOfMove(int,int,int);
		int winState();
		int gameState();
		int read(int,int);
		void setUtility(int);
		int utility();
		sf::Vector2i parent();
};

#endif
