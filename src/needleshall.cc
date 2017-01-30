#include "needleshall.h"
#include "player.h"
#include <iostream>
#include "die.h"
#include "gameboard.h"
using namespace std;

bool NeedlesHall::canGetTimsCup(Player *player) {
	Die timCupChance(1,100);
	int roll = timCupChance.roll();
	if (roll == 1) {
		return gameBoard->giveTimsCup(player);
	} else {
		return false;
	}
}

void NeedlesHall::normalNH(Player *player) {
	Die temp(1,18);
	int pay = 0;
	int roll = temp.roll();
	if(roll == 1){
		pay = -200;
	}
	else if(roll >= 2 && roll <= 3){
		pay = -100;
	}
	else if(roll >= 4 && roll <= 6){
		pay = -50;
	}
	else if(roll >= 7 && roll <= 12){
		pay = 25;
	}
	else if(roll >= 13 && pay <= 15){
		pay = 50;
	}
	else if(roll >= 17 && roll <= 17){
		pay = 100;
	}
	else if(roll == 18){
		pay = 200;
	}
	if(pay == 0){
		cout << "NeedlesHall is not working correctly" << endl;
		return;
	}
	if(player->changeMoney(pay)){
		if(pay > 0){
			cout << "You received $" << pay << " for landing on Needles Hall." << endl;
		}
		else {
			cout << "You lost $" << -1 * pay << " for landing on Needles Hall." << endl;
		}
	}
	else{
		cout << "You lost $" << pay << " from Needles Hall." << endl;
		player->declareBankrupcy();
	}
}

void NeedlesHall::doEvent(Player * player){
	cout << "You have landed on Needles Hall" << endl;
	
	if (gameBoard->getNumTimsCups() >= 4) {
		normalNH(player);
	} else {
		if (!canGetTimsCup(player)) {
			normalNH(player);
		}
	}
}

NeedlesHall::~NeedlesHall(){}

NeedlesHall::NeedlesHall(GameBoard *gameboard): NonPropertyTile(gameboard,"Needles Hall"){}
