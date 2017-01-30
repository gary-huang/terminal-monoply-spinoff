#include "goosenesting.h"
#include "player.h"
#include <iostream>
#include "gameboard.h"
using namespace std;

void GooseNesting::doEvent(Player * actOn){
	cout << "You landed on the Goose Nesting tile, nothing happens." << endl;
}

GooseNesting::~GooseNesting(){}

GooseNesting::GooseNesting(GameBoard *gameboard): NonPropertyTile(gameboard,"Goose Nesting"){}
