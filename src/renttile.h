#ifndef RENTTILE_H
#define RENTTILE_H
#include "propertytile.h"
#include <string>

class RentTile : public PropertyTile {
	const std::string buildingType;
	int numTile;
	int worthToAdd(int numImproves);
	public:
		std::string getBuildingType();
		RentTile(std::string tileName,GameBoard * g,int buyCost,std::string payableType,int payableAmount, std::string buildingType, int numTile);
		~RentTile();
		//std::string getTileName();
		//GameBoard * getGameBoard();
	//void tileEvent(Player * player);
		void buyEvent(Player *player);
		void notifyMonoplyUpdate(Player *owner, int numImproves);
		int calculateResPayableAmount(Player *owner);
		//int calculateGymPayableAmount(Player *owner);
};

#endif

