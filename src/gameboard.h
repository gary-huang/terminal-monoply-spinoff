#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <map>
#include <vector>
#include <string>
#include "tile.h"
//#include "player.h"
#include "controller.h"
#include "monopolytile.h"
#include "renttile.h"
//#include "cups.h"
//#include "die.h"

//bool debugMode = true;

const int NUMTILES = 40;
const int NEWGAMEMONEY = 1500;
//const int MAXTIMSCUPS = 4;
const int MAXPLAYERS = 8; 
const int MINROLL = 1;
const int MAXROLL = 6;
const int T1IMPROVECOST = 50;
const int T2IMPROVECOST = 100;
const int T3IMPROVECOST = 150;
const int T4IMPROVECOST = 200;

// Readable indices for tiles.
enum {OSAP, AL, SLC, ML, TUITION, MKV, ECH, NH1, PAS, HH, TIMS, RCH, PAC, DWE, CPH, 
	UWP, LHI, SLC1, BMH, OPT, GOOSE, EV1, NH2, EV2, EV3, V1, PHYS, B1, 
	CIF, B2, GOTIMS, EIT, ESC, SLC2, C2, REV, NH3, MC, COOP, DC};

class Die;
class Cups;
class Player;
class PropertyTile;

class GameBoard{
	std::map <std::string, std::vector <int> > tuitionTable;
	Tile ** tileGrid;
	int numPlayers;
	Player *players[MAXPLAYERS];
	GameNotification *notification;
	Die * roll1;
	Die * roll2;
	Cups * cupsInGame;
	Player *getPlayerPtr(std::string PlayerFN);
	void readTuitionData();
	bool writePlayer(std::ofstream &ofs, Player *player);
	bool writeTile(std::ofstream &ofs, PropertyTile *tile);
	bool isTileTradeable(MonopolyTile *property);
public:
	// will need to change this ctor to accept players
	GameBoard(GameNotification *notification);
	~GameBoard();
	int getCurrentNumPlayers();
	bool isSymbolInvalid(char symbol);
	bool isSymbolTaken(char symbol);
	int rollDie();
	int getNumTimsCups();
	// function to receive notification from the tiles and 
	// then send an update to the view
	bool addPlayer(Player *p);
	// does not delete the player
	void removePlayer(Player * p);
	void notify(char p,  int oldPos,  int newPos);
	// initializing a player on the board
	void notify(char p);
	// initialize the board when the game is about to start
	void init(); // already have access to # of players
	bool roll(Player * player, int froll = -1, int sroll = -1);
	void doEvent(Player *player, Tile * tile);
	//the difference here is payfeeTims will move you
	void payfeeTims(Player * player, int amount);
	std::string getNameAtLoc(int loc);
	std::string getFirstPlayerName();
	Player *getPlayerAt(int index);
	Tile ** getTileGrid();
	Tile * getTile(int at);
	Tile * getTile(std::string tileName);
	int getTileIndex(std::string tileName);
	int getPlayerIndex(Player *player);
	bool payfee(Player * player, int amount);
	bool useTimsCup(Player * player);
	void tileEvent(Player *player, Tile * tile);
	bool winCheck();
	void auction(PropertyTile * property);
	// money belongs to player 1, property belongs to player 2. DO NOT CALL WITH A GYM OR RES
	void trade(std::string p1,std::string p2, int money, MonopolyTile * property);
	void trade(Player * p1, Player * p2, int money, MonopolyTile * property);
	void trade(std::string p1,std::string p2, int money, RentTile * property);
	void trade(Player * p1, Player * p2, int money, RentTile * property);
	void trade(std::string p1, std::string p2, PropertyTile *prop1, PropertyTile *prop2);
	void trade(Player * p1, Player * p2, PropertyTile *prop1, PropertyTile *prop2);
	void next();
	//void improve();
	// pass the player to make sure that the player actual owns the property
	void mortgageProperty(PropertyTile *property, Player * player);
	// for unmortgaging proerty, im not letting them do it if they do not have enough money(doesnt call bankrupcy)
	void unMortgageProperty(PropertyTile *property, Player * player);
	//void bankrupt();
	bool updateTileInfo(std::string tileName, std::string ownerFN, int numImproves);
	int getTuitionAmount(int numImproves, std::string tileName);
	bool saveGame(std::string fileName, Player *curPlayer);
	void assets(Player *who);
	bool giveTimsCup(Player *who);
	void buyImprovements(Player * player, MonopolyTile * property);
	void sellImprovements(Player * player, MonopolyTile * property);
	bool removeCup(char p);
};

#endif
