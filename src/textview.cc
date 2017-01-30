#include "textview.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int positionOf(char piece) {
	switch (piece) {
		case 'G':
			return G;
		case 'B':
			return B;
		case 'D':
			return D;
		case 'P':
			return P;
		case 'S':
			return S;
		case '$':
			return $;
		case 'L':
			return L;
		case 'T':
			return T;
		default:
			return -1;
	}
}

void TextView::notifyNewPlayer(char p) {
	players.push_back(p);
}

void TextView::notifyRemovePlayer(char p, int pos) {
	changeTileView(p, ' ', pos);
	for (vector<char>::iterator it = players.begin(); it != players.end(); ++it) {
		if (*it == p) players.erase(it);	
		return;
	}
}

TextView::TextView(int numPlayers): View(numPlayers) {
//TextView::TextView(int numPlayers, vector <char> players): View(numPlayers,players) {
	string boardFile = "board.txt";
	ifstream ifs(boardFile.c_str());
	viewGridHeight = VIEWTILEHEIGHT_EXCLUDE_BORDERS * NUMTILESONSIDE + (NUMTILESONSIDE + 1);
	viewGridWidth = VIEWTILEWIDTH_EXCLUDE_BORDERS * NUMTILESONSIDE + (NUMTILESONSIDE + 1);
	//cout << viewGridHeight << "x" << viewGridWidth << endl;
	theGrid = new char*[viewGridHeight];
	for (int k = 0; k < viewGridHeight; ++k) {
		theGrid[k] = new char[viewGridWidth];
	}

	string temp = "";
	for (int k = 0; k < viewGridHeight; ++k) {
		getline(ifs, temp);
//		cout << "GOtline: " << temp << endl;
		istringstream iss(temp);
		iss >> noskipws;
		for (int j = 0; j < viewGridWidth; ++j) {
			char tempChar;
			iss >> tempChar;
			/*if (temp == ' ') {
				cout << "Char: space" << endl;
			} else {
				cout << "Char: " << temp << endl;
			}*/
			theGrid[k][j] = tempChar;
		}
	}
	//for (vector <char>::iterator it = players.begin(); it != players.end(); ++it) {
	//	notifyMove(*it, 0, 0);
	//}
}

void TextView::replaceAt(char c, int row, int col) {
	//cout << row << "x" << col << endl;
	theGrid[row][col] = c;
}

void TextView::changeTileView(char player, char newChar, int pos) {
	const int rowHeight = 5;
	const int colWidth = 10;
	const int tileRow = 4;
	int row = 54;
	int rowFactor = 0;
	int col = 0;

	if (pos >= 0 && pos < 10) {
		rowFactor = 10;
		col = (colWidth * ((pos - 10) * -1)) + 1 + positionOf(player);
	} else if (pos >= 10 && pos < 20) {
		rowFactor = (pos - 20) * -1;
		col = 1 + positionOf(player);
	} else if (pos >= 20 && pos < 30) {
		rowFactor = 0;
		col = (10 * (pos - 20)) + 1 + positionOf(player);
	} else if (pos >= 30 && pos < 40) {
		rowFactor = (pos - 30);
		col = (colWidth * 10) + 1 + positionOf(player);
	} else {
		cerr << "Invalid position" << endl;
		return;
	}
	row = (rowFactor * rowHeight) + tileRow;
	replaceAt(newChar, row, col);
}

void TextView::notifyMove(char p, int oldPos, int newPos){
	// this is where we will notify the actual viewable board
	//int oldPosX, oldPosY;
	changeTileView(p, ' ', oldPos);
	changeTileView(p, p, newPos);
}

void TextView::changeImprovements(int row, int col, int numImprove) {
	//cout << "row: " << row << "col: " << col << endl;
	//cout << numImprove << endl;
	int itr = row;
	int itc = col;
	int itn = 0;
	for (int k = 0; k < numImprove; ++k) {
		replaceAt('I', itr, itc);
		++itc;
	}
	itn = VIEWTILEWIDTH_EXCLUDE_BORDERS - numImprove;
	for (int k = itc; k < (itc + itn); ++k) {
	//	cout << "Replacing: " << "row: " << itr << "col: " << k << endl;
		replaceAt(' ', itr, k);
		//++itc;
	}
}

// pos supplied must be correct. Meaning it must be an improvable tile. 
void TextView::notifyImprovements(int pos, int numImprove) {
	//cout << "Pos: " << pos << endl;
	const int rowHeight = 5;
	const int colWidth = 10;
	const int tileRow = 1;
	int row = 54;
	int rowFactor = 0;
	int col = 0;
	if (numImprove < 0 || numImprove > 5) return;
	if (pos >= 0 && pos < 10) {
		rowFactor = 10;
		col = (colWidth * ((pos - 10) * -1)) + 1;
	} else if (pos >= 10 && pos < 20) {
		rowFactor = (pos - 20) * -1;
		col = 1;
	} else if (pos >= 20 && pos < 30) {
		rowFactor = 0;
		col = (10 * (pos - 20)) + 1;
	} else if (pos >= 30 && pos < 40) {
		rowFactor = (pos - 30);
		col = (colWidth * 10) + 1;
	} else {
		//cerr << "Invalid position" << endl;
		return;
	}
	row = (rowFactor * rowHeight) + tileRow;
	changeImprovements(row, col, numImprove);
}

void TextView::print(){
	for (int k = 0; k < viewGridHeight; ++k) {
		for (int j = 0; j < viewGridWidth; ++j) {
			cout << theGrid[k][j];
		}
		cout << endl;
	}
	/*for (vector <char>::iterator it = players.begin(); it != players.end(); ++it) {
		cout << *it << endl;
	}*/
}

TextView::~TextView(){
	for (int k = 0; k < viewGridHeight; ++k) {
		delete [] theGrid[k];
	}
	delete [] theGrid;
}
