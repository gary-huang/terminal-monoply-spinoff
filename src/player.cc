#include "player.h"
#include <iostream>
#include "tile.h"
#include "monopolytile.h"
#include "gameboard.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;

bool Player::changeMoney(int change){
	amountMoney+=change;
	worth += change;
	if(amountMoney < 0){
		return false;
	}
	return true;
	// return false if the player is bankrupt
}
int Player::getAmountOwed(){ return amountOwed;}
void Player::setAmountOwed(int amount){ amountOwed = amount;};
bool Player::getToDelete(){ return toDelete; }
void Player::setToDelete(bool expr){ toDelete = expr;}

bool Player::getRestrictedCommands(){ return restrictedCommands;}
void Player::setRestrictedCommands(bool expr) { restrictedCommands = expr;};

int Player::getRollsInRow(){return rollsInRow;}
void Player::setRollsInRow(int amt){rollsInRow = amt;}
int Player::getMoney(){ return amountMoney;	}

int Player::getPos(){ return tilePosition; }

GameBoard * Player::getGame(){ return game; }

string Player::getFullName(){return fullName;}

//int * Player::getOwned(){ return tilesOwned; }
int Player::getTimsCups(){ return timsCups; }

char Player::getCharName() { return charName; }

void Player::removeTilesOwned(int removeTile){
	//int size = tilesOwned.size();
	//cout << "tileto remove:" << removeTile << endl;
	for (vector<int>::iterator i = tilesOwned.begin(); i != tilesOwned.end(); ++i){
		//cout << "Tile owned:" << *i << endl;
		if(*i == removeTile){
			tilesOwned.erase(i);
			return;
		}
	}
}

Player * Player::getOweDebtTo(){
	return oweDebtTo;
	
}
void Player::setOweDebtTo(Player * player){ oweDebtTo = player;}

// current player sells and remove assets

void Player::removeAndSellAssets(Player *player, Player * player2){
	int size = tilesOwned.size();
	string playerName = player->getFullName();
	int tempArr[size];
	for (int i = 0; i < size; ++i){
		tempArr[i] = tilesOwned[i];
	}
	game->removePlayer(player);
	if(player2 == NULL){
		// auction assets
		for (int i = 0; i < size; ++i){
			Tile * tp = game->getTile(tempArr[i]);
			PropertyTile * ptp = dynamic_cast<PropertyTile *>(tp);
			game->auction(ptp);
		}
		for (int k = 0; k < player->getTimsCups(); ++k) {
			game->removeCup(player->getCharName());
		}
		player->setTimsCups(0);
		// update everyones monopoly
		for(int i = 0; i < game->getCurrentNumPlayers(); i++){
			Player * cur = game->getPlayerAt(i);
			cur->checkMonopoly();
		}
	}
	else{
		// give assets to p2
		for (int k = 0; k < player->getTimsCups(); ++k) {
			game->removeCup(player->getCharName());
			game->giveTimsCup(player2);
		}
		player2->changeMoney(player->getAmountOwed());
		player2->changeWorth(player->getAmountOwed());
		player->setTimsCups(0);
		for (int i = 0; i < size; ++i){
			Tile * tp = game->getTile(tempArr[i]);
			PropertyTile * ptp = dynamic_cast<PropertyTile *>(tp);
			// fnction for the player to receive a building
			ptp->setOwner(player2);
			player2->changeWorth(ptp->getCost());
			player2->tilesOwned.push_back(tempArr[i]);
			cout << player2->getFullName() << " now owns " << ptp->getTileName() << endl;
		}
		player2->checkMonopoly();
	}
	// lets see if this was the last opponenet to the winner
	 player->setToDelete(true);
	cout << playerName << " has lost the game and declared bankrupcy, better luck next time!" << endl;
}

// if they rasie enough money, this will produce true
bool Player::declareBankrupcy(){
	string command2;
	if(getMoney() > 0) return true;
	cout << getFullName()  << ", you may only trade, mortgage, and sell improvemets to stay in the game." <<endl;
	cin.clear();
	cin.ignore();
		getline(cin,command2);
		istringstream iss(command2);
		string command;
		iss >> command;
		if(command == "improve"){
			//sellImprovements();
			string property;
			string sell;
			iss >> property >> sell;
			MonopolyTile * temp = dynamic_cast<MonopolyTile *>(getGame()->getTile(property));
			getGame()->sellImprovements(this,temp);
			if(getMoney() < 0){
				return declareBankrupcy();
			}
			else{
				return true;
			}
		}
		else if(command == "mortgage"){
				string property2;
				iss >> property2;
				Tile * tile = getGame()->getTile(property2);
				PropertyTile * temp = static_cast<PropertyTile *>(tile);
				game->mortgageProperty(temp,this);
			
			if(getMoney() < 0){
				return declareBankrupcy();
			}
			else{
				return true;
			}
		}
		else if(command == "bankrupt"){
		//	removeAndSellAssets(this,NULL);
			removeAndSellAssets(this ,getOweDebtTo()); 
			//game->removePlayer(this);
			return false;
		}
		else if(command == "trade"){
			string name,building;
			int money;
			iss >> name >> building >> money;
			// need to get the tile for building
			Tile * temp = game->getTile(building);
			if(temp == NULL){
				cout << "building does not exist" << endl;
			}
			else{
				MonopolyTile * mtp = dynamic_cast<MonopolyTile *>(temp);
				if(mtp){
					game->trade(name,getFullName(),money,mtp);
				}
				else{// this means its a rent tile
					RentTile * rtp = dynamic_cast<RentTile *>(temp);
					game->trade(name,getFullName(),money,rtp);
				}
			}
			if(getMoney() < 0){
						return declareBankrupcy();
				}
				else{
					return true;
				}
	} else if(command == "assets"){
		printAssets();
	}
	return true;
}

bool Player::declareBankrupcy(Player *OwingPlayer, int owed){
	if(declareBankrupcy()){
		OwingPlayer->changeMoney(owed);
		return true;
	}
	return false;
}

// Setter for Pos is making a turn. tf call it with the getter + dice roll
void Player::setPos(int newPos){ tilePosition = newPos;}

// setters and getters for the new fields i added
void Player::setTimsLine(bool exp){ timsLine = exp; }

bool Player::getTimsLine() { return timsLine; }

void Player::setTurnsInLine(int amount){ turnsInLine = amount ; }

int Player::getTurnsinLine() { return turnsInLine; }

int Player::getSumLastDieRoll() { return sumLastDieRoll ; }

void Player::setSumLastDieRoll(int amount){ sumLastDieRoll = amount ;} 

void Player::setTimsCups(int amount) { timsCups = amount;}

// this adds a tile to the vector that you own
void Player::addTilesOwned(int addTo){
	tilesOwned.push_back(addTo);
}
// this will determine how many gyms you own without having to save a field and update it
int Player::getGymsOwned(){
	int gymsOwned = 0;
	int size = tilesOwned.size();
	for (int i = 0; i < size; ++i){
		if(tilesOwned[i] == CIF || tilesOwned[i] == PAC){
			gymsOwned++;
		}
	}
	return gymsOwned;
}
// this will determine res's owned without hollding a field
int Player::getResOwned(){
	int resOwned = 0;
	int size = tilesOwned.size();
	for (int i = 0; i < size; ++i){
		if(tilesOwned[i] == V1 || tilesOwned[i] == UWP || tilesOwned[i] == REV || tilesOwned[i] == MKV){
			resOwned ++;
		}
	}
	return resOwned;
}

bool Player::hasMonopoly(string monopolyName) {
	for (vector <string>::iterator it=monopolyOwner.begin(); it != monopolyOwner.end(); ++it) {
		if (monopolyName != *it) return true;
	}
	return false;
}

//check if you own a monopoly after you buy it
void Player::checkMonopoly(){
	monopolyOwner.clear();
	if((find(tilesOwned.begin(), tilesOwned.end(), 1)!= tilesOwned.end()) &&
			(find(tilesOwned.begin(), tilesOwned.end(), 3) != tilesOwned.end())){
				monopolyOwner.push_back("Arts1");
	}
	if(find(tilesOwned.begin(), tilesOwned.end(), 6) != tilesOwned.end() &&
			find(tilesOwned.begin(), tilesOwned.end(), 8) != tilesOwned.end() &&
				find(tilesOwned.begin(), tilesOwned.end(), 9) != tilesOwned.end()){
				monopolyOwner.push_back("Arts2");
	}
	if(find(tilesOwned.begin(), tilesOwned.end(), 11) != tilesOwned.end() &&
			find(tilesOwned.begin(), tilesOwned.end(), 13) != tilesOwned.end() &&
				find(tilesOwned.begin(), tilesOwned.end(), 14) != tilesOwned.end()){
				monopolyOwner.push_back("Eng");
	}
	if(find(tilesOwned.begin(), tilesOwned.end(), 16) != tilesOwned.end() &&
			find(tilesOwned.begin(), tilesOwned.end(), 18) != tilesOwned.end() &&
				find(tilesOwned.begin(), tilesOwned.end(), 19) != tilesOwned.end()){
				monopolyOwner.push_back("Health");
	}
	if(find(tilesOwned.begin(), tilesOwned.end(), 21) != tilesOwned.end() &&
			find(tilesOwned.begin(), tilesOwned.end(), 23) != tilesOwned.end() &&
				find(tilesOwned.begin(), tilesOwned.end(), 24) != tilesOwned.end()){
				monopolyOwner.push_back("Env");
	}
	if(find(tilesOwned.begin(), tilesOwned.end(), 26) != tilesOwned.end() &&
			find(tilesOwned.begin(), tilesOwned.end(), 27) != tilesOwned.end() &&
				find(tilesOwned.begin(), tilesOwned.end(), 29) != tilesOwned.end()){
				monopolyOwner.push_back("Sci1");
	}
	if(find(tilesOwned.begin(), tilesOwned.end(), 31) != tilesOwned.end() &&
			find(tilesOwned.begin(), tilesOwned.end(), 32) != tilesOwned.end() &&
				find(tilesOwned.begin(), tilesOwned.end(), 34) != tilesOwned.end()){
				monopolyOwner.push_back("Sci2");
	}
	if(find(tilesOwned.begin(), tilesOwned.end(), 37) != tilesOwned.end() &&
			find(tilesOwned.begin(), tilesOwned.end(), 39) != tilesOwned.end()){
				monopolyOwner.push_back("Math");
	}
}
void Player::setInBid(bool exp){ inBid = exp;}
bool Player::getInBid(){ return inBid;}
//Player::Player(): fullName(""), charName(0), tilePosition(0), amountMoney(NEWGAMEMONEY), timsCups(0), timsLine(false), turnsInLine(0), sumLastDieRoll(0),inBid(false) {}

Player::Player(string fullName, char symbol, int numTimsCup, int amountMoney, int position,
			 int isInTimsLine, int turnsInTimsLine, GameBoard * game):
	fullName(fullName), charName(symbol),tilePosition(position), amountMoney(amountMoney), timsCups(numTimsCup),  
		sumLastDieRoll(0), inBid(false), worth(amountMoney), game(game),rollsInRow(0),toDelete(false),oweDebtTo(NULL),restrictedCommands(false),amountOwed(0){
		if (isInTimsLine == 1) {
			timsLine = true;
			turnsInLine = turnsInTimsLine;
		} else { // not even in tims line tile
			timsLine = false;
			turnsInLine = 0;
		}
		for (int k = 1; k <= numTimsCup; ++k) {
			game->giveTimsCup(this);
			--timsCups;
		}
		
	} //Ctor used for quick load

void Player::changeWorth(int amount){
	worth += amount;
}

int Player::getWorth(){
	return worth;
}

void Player::printAssets() {
	cout << endl;
	cout << "-----------------------------------------------Asset Information-----------------------------------------------" << endl;
	cout << "Player Piece: " << getCharName();
	for (int k = 0; k < 15; ++k) {
		cout << " ";
	}
	cout << "Player Name: " << getFullName() << endl;
	cout << "Currently on tile: " << (game->getTile(getPos()))->getTileName() << endl;
	cout << "Savings: $" << getMoney();
	for (int k = 0; k < 15; ++k) {
		cout << " ";
	}
	cout << "Number of Tim's Cups in your possession: " << timsCups << endl;
	if (getTimsLine()) {
		cout << "Also worth noting that you are stuck in DC Tim's Line. Turns served in line: " << getTurnsinLine() << endl;
	}
	cout << "Properties owned:";
	if (tilesOwned.empty()) {
		cout << " None" << endl;
	} else {
		for (vector <int>::iterator it=tilesOwned.begin(); it != tilesOwned.end(); ++it) {
			cout << " ";
			int tileOwnedPos = *it;
			cout << (game->getTile(tileOwnedPos))->getTileName();
		}
		cout << endl;
	}
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}

void Player::getOutOfTims(int froll, int sroll) {
	setTurnsInLine(0);
	setSumLastDieRoll(froll+sroll);
	setTimsLine(false);
}

void Player::move(int froll, int sroll) {
	int oldPos = getPos();
	setSumLastDieRoll(froll + sroll);
	setPos(getPos() + getSumLastDieRoll());
	if(getPos() >= 40){
		setPos(getPos() - 40);
		// if you arent on the collect osat tile, collect osap anyway
		if(getPos() != 0) {
			changeMoney(200);
			cout << "You get $200 as you collect OSAP funding!" << endl;
		}
	}
	game->notify(getCharName(), oldPos, getPos());
	cout << "Your first roll was " << froll << " and your second roll was " << sroll << "." << endl;
	game->tileEvent(this, game->getTileGrid()[getPos()]);

}
