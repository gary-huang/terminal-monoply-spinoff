#ifndef MONOPOLYTILE_H
#define MONOPOLYTILE_H
#include <string>
#include "propertytile.h"
class GameBoard;
class Player;

class MonopolyTile : public PropertyTile{
	const std::string monopolyName;
	int numImprove;
	const int improveCost;
	int numTile;
	int worthToAdd();
public:
	std::string getMonopolyName();
	int getImproveCost();
	int getNumImprove();
	void setNumImprove(int newVal);
	//int getNumTile();
	//std::string getTileName();
	//GameBoard * getGameBoard();
	MonopolyTile(std::string monopolyName, std::string name, int improveCost,int buyCost,int payableAmount, GameBoard *g,int numTile);
	void buyEvent(Player *player);
	void notifyMonoplyUpdate(Player *owner, int numImproves);
};

#endif

