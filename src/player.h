#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "tile.h"
#include <vector>
class GameBoard;

class Player{
	std::string fullName;
	char charName;
	int tilePosition;
	int amountMoney;
	std::vector<int> tilesOwned;
	int timsCups;
	std::vector<std::string> monopolyOwner;
	bool timsLine;	
	int turnsInLine;
	int sumLastDieRoll;
	bool inBid;
	int worth;
	GameBoard * game;
	int rollsInRow;
	bool toDelete;
	Player *oweDebtTo;
	bool restrictedCommands;
	int amountOwed;
	// new fields for # of rent tiles and gym tiles
public:
	// note: changeMoney is an adder, not a setter
	int getAmountOwed();
	void setAmountOwed(int amount);
	bool getRestrictedCommands();
	void setRestrictedCommands(bool expr);
	Player * getOweDebtTo();
	void setOweDebtTo(Player * player);
	bool getToDelete();
	void setToDelete(bool expr);
	bool changeMoney(int change);
	int getMoney();
	int getPos();
	GameBoard * getGame();
	void setPos(int newPos);
	char getCharName();
	std::string getFullName();
	void setInBid(bool exp);
	bool getInBid();
	int getRollsInRow();
	void setRollsInRow(int amt);
	//int * getOwned();
	//Trying to avoid holding the gyms,res owned in a field
	int getGymsOwned();
	int getResOwned();
	bool hasMonopoly(std::string monopolyName);
	int getTimsCups();
	void setTimsCups(int amount);
	bool declareBankrupcy();

	bool declareBankrupcy(Player *OwingPlayer, int owing);
	void addTilesOwned(int addTo);
	void removeTilesOwned(int removeTile);
	void sellImprovements();
	void checkMonopoly();
	// new functions for timsline problem
	void setTimsLine(bool exp);
	bool getTimsLine();
	void setTurnsInLine(int amount);
	int getTurnsinLine();
	int getSumLastDieRoll();
	void setSumLastDieRoll(int amount);
	void changeWorth(int amount);
	int getWorth();
	void printAssets();
	void move(int froll, int sroll);
	void getOutOfTims(int froll, int sroll);
	/// still need to impliment
	//std::vector<int> getTilesOwned;
	// this function will remove the player and sell his assets
	// if p2 != Null the assets go to him.(if a property is mortgaged he only hass to pay 10% for it)
	void removeAndSellAssets(Player *player, Player * player2);
	
	// Player ctor & dtor
	//Player();
	Player(std::string fullName, char symbol, int numTimsCup, int amountMoney, 
			int position, int isInTimsLine, int turnsInLine, GameBoard * game); //Ctor used for quick load
	//~Player();
};

#endif
