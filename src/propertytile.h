#ifndef PROPERTYTILE_H
#define PROPERTYTILE_H
#include "tile.h"
#include <string>

class Player;
class GameBoard;

class PropertyTile: public Tile{
	int buyCost;
	std::string payableType;
	int payableAmount;
	Player * owner;
	bool mortgaged;
	// inherited: tileName, gameboard *
public:
	int getCost();
	void setMortgaged(bool expr);
	bool getMortgaged();
	void setPayableAmount(int newAmount);
	std::string getPayableType();
	int getPayableAmount();
	Player * getOwner();
	void setOwner(Player * newOwner);
	PropertyTile(std::string tileName, GameBoard * g, int buyCost, std::string payableType, int payableAmount, Player * owner);
	virtual ~PropertyTile() = 0;
};

#endif
