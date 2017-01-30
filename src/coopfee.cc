#include "coopfee.h"
#include "player.h"
#include <iostream>
#include "gameboard.h"
using namespace std;

void CoopFee::doEvent(Player * player){
	// pay 150
	cout << "Oh no, you landed on the Coop Fee tile, pay $150 to the bank please." << endl;
	if(player->changeMoney(-150)){
		cout << "Thank you for the payment, you now have $" << player->getMoney() << "." << endl;
	}
	else{
		cout << "You do not have enough to pay the bank." << endl;
		player->declareBankrupcy(); 
	}
}
CoopFee::~CoopFee(){}

CoopFee::CoopFee(GameBoard *gameboard): NonPropertyTile(gameboard, "Coop Fee"){}
