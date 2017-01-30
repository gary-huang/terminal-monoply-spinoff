#include "tuition.h"
#include "player.h"
#include <iostream>
#include "gameboard.h"
using namespace std;
void Tuition::doEvent(Player *	player){
	int pay = player->getWorth() * .1;
	cout << "You landed on the Tuition tile, " <<
		"you can pay 10% of your overall worth, or $300, type '10' to pay 10% of worth and 'money' to pay $300:" << endl;
	string command;
	while(cin >> command){
		if(command == "10"){
			if	(player->changeMoney(-1*pay)){
				cout << "You now have $" <<	player->getMoney() << endl;
			} else {
				player->declareBankrupcy(); 
			}
			return;
		} else if(command == "money"){
			if(player->changeMoney(-1 * 300)){
				cout << "You now have $" <<	player->getMoney() << endl;
			} else {
				player->declareBankrupcy();
			}
			return;
		} else if (command == "assets") {
			cout << "Can't check your assets while on a tuition tile deciding how to pay for tuition!" << endl;
		} else {
			cout << "Not a valid command, please try again" << endl;
		}
	}
}
Tuition::~Tuition(){}
Tuition::Tuition(GameBoard *gameboard): NonPropertyTile(gameboard,"Tuition"){}
