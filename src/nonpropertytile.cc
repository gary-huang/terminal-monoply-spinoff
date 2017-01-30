#include "nonpropertytile.h"

NonPropertyTile::NonPropertyTile(GameBoard *gameboard, std::string tileName):Tile(gameboard,tileName){}

NonPropertyTile::~NonPropertyTile(){}

void NonPropertyTile::notifyMonoplyUpdate(Player *owner, int numImproves) {}
