#include "gototims.h"
#include "player.h"
#include "gameboard.h"
#include <iostream>
using namespace std;

void GoToTims::doEvent(Player * player){
	int oldPos = player->getPos();
	player->setPos(10);
	player->setTimsLine(true);
	player->setTurnsInLine(0);
	getGameBoard()->notify(player->getCharName(),oldPos,10);
	cout << "Player " << player->getFullName() << " has been sent to the Tims line" << endl;
}

GoToTims::~GoToTims(){}

GoToTims::GoToTims(GameBoard *gameboard): NonPropertyTile(gameboard,"Go To Tims"){}
