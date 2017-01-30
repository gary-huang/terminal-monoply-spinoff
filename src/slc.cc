#include "slc.h"
#include "player.h"
#include "gameboard.h"
#include "die.h"
#include <iostream>
using namespace std;

bool Slc::canGetTimsCup(Player *player) {
	Die timCupChance(1,100);
	int roll = timCupChance.roll();
	if (roll == 1) {
		return gameBoard->giveTimsCup(player);
	} else {
		return false;
	}
}

void Slc::move(Player *player) {
	int oldPos = player->getPos();
	Die temp(1,24);
	int rollTo;
	int roll = temp.roll();
	if(roll >= 1 && roll <= 3){
		rollTo = player->getPos()-3;
	}
	else if(roll >= 4 && roll <= 7){
		rollTo = player->getPos()-2;
	}
	else if(roll >= 8 && roll <= 11){
		rollTo = player->getPos()-1;
	}
	else if(roll >= 12 && roll <= 14){
		rollTo = player->getPos()+1;
	}
	else if(roll >= 15 && roll <= 18){
		rollTo = player->getPos()+2;
	}
	else if(roll >= 19 && roll <= 22){
		rollTo = player->getPos()+3;
	}
	else if(roll == 23){
		rollTo = 10;
		//some how update to making them move in game
	}
	else{// roll =- 24
		rollTo = 0;
	}
	if(rollTo > 40) rollTo = rollTo -40;
	if(rollTo < 0)rollTo = rollTo + 40;
	player->setPos(rollTo);
	gameBoard->notify(player->getCharName(),oldPos,player->getPos());
	cout << "The SLC tile sent you to " << gameBoard->getNameAtLoc(rollTo)<< endl;
	gameBoard->tileEvent(player,gameBoard->getTileGrid()[player->getPos()]);
}

void Slc::doEvent(Player * player){
	cout << "You have landed on SLC" << endl;
	
	if (gameBoard->getNumTimsCups() >= 4) {
		move(player);
	} else {
		if (!canGetTimsCup(player)) {
			move(player);
		}
	}

	
}

Slc::~Slc(){}

Slc::Slc(GameBoard *gameboard): NonPropertyTile(gameboard,"SLC"){}
