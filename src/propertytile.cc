#include "propertytile.h"
#include "player.h"
#include "gameboard.h"
using namespace std;
int PropertyTile::getCost(){ return buyCost; }

string PropertyTile::getPayableType(){return payableType;}

int PropertyTile::getPayableAmount(){ return payableAmount;}

Player * PropertyTile::getOwner(){return owner;}

PropertyTile::PropertyTile(string tileName, GameBoard * g,int buyCost,string payableType,int payableAmount, Player * owner): Tile(g, tileName),buyCost(buyCost),
							payableType(payableType),payableAmount(payableAmount),owner(owner),mortgaged(false){}

PropertyTile::~PropertyTile(){}

void PropertyTile::setPayableAmount(int newAmount){
	payableAmount = newAmount;
}
void PropertyTile::setOwner(Player * newOwner){
	owner = newOwner;
}


void PropertyTile::setMortgaged(bool expr){ mortgaged = expr;}

bool PropertyTile::getMortgaged(){return mortgaged;}
