#include "monopolytile.h"
#include "gameboard.h"
#include "player.h"
using namespace std;

string MonopolyTile::getMonopolyName(){
	return this->monopolyName;
}
int MonopolyTile::getImproveCost(){
	return this->improveCost;
}
int MonopolyTile::getNumImprove(){
	return this->numImprove;
}
void MonopolyTile::setNumImprove(int newVal){
	numImprove = newVal;
}
MonopolyTile::MonopolyTile(string monopolyName, string name, int improveCost, int buyCost,int payableAmount, GameBoard *g, int numTile): PropertyTile(name,g,buyCost,"Tuition",payableAmount,NULL)
																										,monopolyName(monopolyName), numImprove(0), improveCost(improveCost), numTile(numTile){}

//string MonopolyTile::getTileName(){ return tileName; }

//GameBoard * MonopolyTile::getGameBoard(){ return gameBoard; }

void MonopolyTile::buyEvent(Player *player){
	// frst see if the monpoly tile has an ower, if it does  you need to find the tuition player has to pay
	if(getMortgaged() == true){
		cout << "This property is morgaged. No transaction of money needed." << endl;
		return ;
	}
	if(getOwner() != NULL){
//		int improve = getNumImprove();
		int owed = getPayableAmount();
		if(getOwner()->getFullName() == player->getFullName()){
			cout << "You own this tile, nothing happens." << endl;
			return ;
		}
		if(!player->changeMoney(-1*owed)){
			cout << "You had to pay " << getOwner()->getFullName() << " $" << owed << ", but you can't afford it!" << endl;
			player->setOweDebtTo(getOwner());
			player->setAmountOwed(owed);
			player->setRestrictedCommands(true);
			if(player->declareBankrupcy(getOwner(),owed)){
				//getOwner()->changeMoney(owed);	
				cout << player->getFullName() << " raised enough money" << endl;			
			}
			else{
				//player->removeAndSellAssets(player,getOwner());
			}
			//cout << "bankrupt" << endl;
		} else {
			getOwner()->changeMoney(owed);
			cout << "You had to pay " << getOwner()->getFullName() << " $" << owed << ". Unlucky!" << endl;
			return;
		}
	} else {
		cout << "Would you like to buy " << tileName << " ? " << "The price is " << getCost() << "$" << endl;
		cout << "You have " << player->getMoney() << "$" << endl;
		cout << "Type Y for yes and N for no" << endl;
		string command;
		while(cin >> command){
			if(command == "Y"){
				if(player->changeMoney(-1*getCost())){
					// you can buy it
					setOwner(player);
					player->addTilesOwned(numTile);
					player->changeWorth(getCost());
					player->checkMonopoly();
					cout << "You successfully bought " << tileName << ", you now have $" << player->getMoney() << "." << endl;
				}
				else{
					if(player->declareBankrupcy()){
						setOwner(player);
						player->addTilesOwned(numTile);
						player->changeWorth(getCost());
						player->checkMonopoly();
						cout << "You successfully bought " << tileName << ", you now have $" << player->getMoney() << "." << endl;
					}
					else{
						cout << "Property not bought" << endl;
					}
					// user will have to morgage property aor sell improvements to make up the money aka bankrupt ======================================================================
				}
				return;
			}
			else if(command == "N"){
				cout << "You decided to not buy the property." << endl;
				gameBoard->auction(this);
				break;
			}
			else{
				cout << "That is not a valid command, please try again." << endl;
			}
		} // while
	}
}


int MonopolyTile::worthToAdd() {
	if (numImprove <= -1) {
		return (getCost() / 2);
	} else {
		return (getCost() + (numImprove * getImproveCost()));
	}
}

void MonopolyTile::notifyMonoplyUpdate(Player *owner, int numImproves) {
	//cout << getTileName() << endl;
	setOwner(owner);
	numImprove = numImproves;
	if (numImproves == -1) {
		setMortgaged(true);
	} else {
		setMortgaged(false);
	}
	//cout << "YA" << endl;
	
	if (numImproves > -1) {
		GameBoard *g = getGameBoard();
		int payable = g->getTuitionAmount(numImproves, getTileName());
		setPayableAmount(payable);
		//cout << getTileName() << " with improvements " << numImproves << " has NEW PAYABLE: " << getPayableAmount() << endl;
	} else {
		setPayableAmount(0);
		//cout << "Mortaged " << getTileName() << " with improvements " << numImproves << " has NEW PAYABLE: " << getPayableAmount() << endl;
	}
/*	cout << getTileName() << endl;
	cout << "Numimproves: " << numImprove << endl;
	int k = worthToAdd();
	cout << k << endl;*/
	if (owner) {
		owner->changeWorth(worthToAdd());
		int tileIndex = (getGameBoard())->getTileIndex(getTileName());
		owner->addTilesOwned(tileIndex);
	}

}
