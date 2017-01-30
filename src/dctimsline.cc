#include "collectOSAP.h"
#include "player.h"
#include <iostream>
#include "dctimsline.h"
#include "gameboard.h"
using namespace std;

void DCTimsLine::doEvent(Player *player){
	cout <<"You narrowly escape the DC tims line by just walking past it" << endl;
}

DCTimsLine::DCTimsLine(GameBoard *gameboard):NonPropertyTile(gameboard,"DC Tims Line"){}

DCTimsLine::~DCTimsLine(){}
