#include <string>
#include "tile.h"
#include "gameboard.h"
#include "player.h"
using namespace std;

string Tile::getTileName() { return tileName; }

GameBoard * Tile::getGameBoard(){ return gameBoard; }

Tile::Tile(GameBoard * gameBoard,string tileName): gameBoard(gameBoard), tileName(tileName) {}

//string getTileName();
//		GameBoard * getGameBoard();

Tile::~Tile(){}
