#include "renttile.h"
//#include <string>
#include <iostream>
#include "player.h"
#include "gameboard.h"
using namespace std;

string RentTile::RentTile::getBuildingType(){
	return buildingType;
}
RentTile::RentTile(string tileName,GameBoard * g,int buyCost,string payableType,int payableAmount,string buildingType,int numTile):
				PropertyTile(tileName,g,buyCost,payableType,payableAmount,NULL),buildingType(buildingType),numTile(numTile){}
RentTile::~RentTile(){}
// already shuould inherit the  setter for payable amount! important to this class

//string RentTile::getTileName(){return tileName;}
//GameBoard * RentTile::getGameBoard(){ return gameBoard; }

int RentTile::calculateResPayableAmount(Player *owner){
	int owed = 0;
	int resOwned = owner->getResOwned();
	//cout << resOwned << endl;
	if (getMortgaged()) return 0;
	if (resOwned <= 0) owed = 25;
	if(resOwned <= 2) owed = 25 * resOwned;
	if(resOwned == 3) owed = 100;
	if(resOwned == 4) owed = 200;
	return owed;
}

void RentTile::buyEvent(Player *player){
	// frst see if the monpoly tile has an ower, if it does  you need to find the tuition player has to pay
	if(getMortgaged() == true){
		cout << "This property is morgaged. No transaction of money needed." << endl;
		return ;
	}
	// this is the calculation for if it is a gym
	int owed = 0;
	if(getOwner() != NULL){
		if(getOwner()->getFullName() == player->getFullName()){
				cout << "You own this tile, nothing happens." << endl;
				return ;
			}
		cout <<"The owner of the property is " << getOwner()->getFullName() << "." << endl;
		if(getPayableType() == "Tuition"){ // this means it is a gym
			int dieRoll = gameBoard->rollDie();
			// is it going to be 10 or 4
			int multiplyFactor = 0;
			if(getOwner()->getGymsOwned() == 1) multiplyFactor = 4;
			if(getOwner()->getGymsOwned() == 2) multiplyFactor = 10;
			owed = getPayableAmount() + dieRoll*multiplyFactor;
			if(!player->changeMoney(-1*owed)){
				player->declareBankrupcy(getOwner(),owed);
			} else{
				getOwner()->changeMoney(owed);
				cout << "You had to pay " << getOwner()->getFullName() << " " <<  owed << "$. Unlucky!" << endl;
			}
		} else{// this means it is a res, pays rent
			owed = calculateResPayableAmount(getOwner()); // do it on the owner
			if(!player->changeMoney(-1*owed)){
				player->declareBankrupcy(getOwner(),owed);
			} else{
				getOwner()->changeMoney(owed);
				cout << "You had to pay " << getOwner()->getFullName() << " " << owed << "$. Unlucky!" << endl;
				return;
			}
		}
	} else {
		cout << "Would you like to buy " << tileName << " ? " << "The price is " << getCost() << endl;
		cout << "You have " << player->getMoney() << " money" << endl;
		cout << "Type Y for yes and N for no" << endl;
		string command;
		while(cin >> command){
			if(command == "Y"){
				if(player->changeMoney(-1*getCost())){
					// you can buy it
					setOwner(player);
					player->addTilesOwned(numTile);
					cout << "You successfully bought " << tileName << ", you now have " << player->getMoney() << "$" << endl;
					return;
				} else{
					if(player->declareBankrupcy()){
						setOwner(player);
						player->addTilesOwned(numTile);
						player->changeWorth(getCost());
						cout << "You successfully bought " << tileName << ", you now have $" << player->getMoney() << "." << endl; 
					}
					else{
						cout << player->getFullName() << " was not able to raise enough money to buy tile." << endl;
					}
					return;
				}
				break;
			} else if(command == "N"){
				gameBoard->auction(this);
				break;
			} else{
				cout << "That is not a valid command, please try again." << endl;
			}
		}
	}
}

int RentTile::worthToAdd(int numImproves) {
	if (numImproves <= -1) {
		return (getCost() / 2);
	} else {
		return getCost();
	}
}

void RentTile::notifyMonoplyUpdate(Player *owner, int numImproves) {
	setOwner(owner);
	if (owner) {
		owner->changeWorth(worthToAdd(numImproves));
		int tileIndex = (getGameBoard())->getTileIndex(getTileName());
		owner->addTilesOwned(tileIndex);
		//owner->setResOwned(owner->getResOwned() + 1);
	}

	if (numImproves == -1) {
		setMortgaged(true);
		setPayableAmount(0);
		//cout << "Mortgaged " << getTileName() << " has rent " << getPayableAmount() << endl;
	} else {
		setMortgaged(false);
		if (owner) setPayableAmount(calculateResPayableAmount(owner));
		//cout << getTileName() << " has rent " << getPayableAmount() << endl;
	}	
}
