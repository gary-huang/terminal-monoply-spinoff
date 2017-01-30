#ifndef TILE_H
#define TILE_H
#include <string>

class GameBoard;
class Player;

class Tile {
	protected:
		GameBoard * gameBoard;
		std::string tileName;
	public:
		std::string getTileName();
		GameBoard * getGameBoard();
		Tile(GameBoard * gameboard, std::string tileName);
		virtual void notifyMonoplyUpdate(Player *owner, int numImproves) = 0;
		virtual ~Tile() = 0; 
};

#endif
