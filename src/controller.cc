#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "controller.h"
#include "gameboard.h"
#include "textview.h"
#include "player.h"
using namespace std;

GameNotification::GameNotification(): curPlayer(NULL) {}

GameNotification::~GameNotification() {
	curPlayer = NULL;
}

Controller::Controller(string loadFile): GameNotification(), td(NULL), game(NULL), loadFile(loadFile), testing(false), rolled(false) {}

int isInt(string str) {
	istringstream iss(str);
	int temp;
	iss >> temp;
	if (iss.fail()) return -1;
	return temp;
}

void Controller::addPlayer(istream &input, int mode) {
	string fullName = "";
	if (mode == NEW || mode == NEW_TEST) cout << "Enter player's name: ";
	input >> fullName;
	char symbol = 'G';
	bool unavailable = false;
	//cout << endl;
	do {
		if (mode == NEW || mode == NEW_TEST) {
			cout << "Choose a piece, input must be 1 character only, and one of G, B, D, P, S, $, L, T" << endl;
			cout << "Enter player's symbol: ";
		}

		input >> symbol;
		if (input.fail()) continue;
		//cout << endl;
		unavailable = game->isSymbolInvalid(symbol);
		if (unavailable) continue;
		unavailable = game->isSymbolTaken(symbol);
		
		//if (unavailable) cout << "Symbol already taken, choose another." << endl;
		//cout << "Y" << endl;
	} while (unavailable);
	int numTimsCup = 0;
	int amountMoney = NEWGAMEMONEY;
	int position = 0;
	int isInTimsLine = 0;
	int turnsInLine = 0;
	if (mode == LOAD || mode == LOAD_TEST) {
		input >> numTimsCup;
		input >> amountMoney;
		input >> position;
		if (position == TIMS) {
			input >> isInTimsLine;
			if (isInTimsLine != 0) input >> turnsInLine;
		}
	} 
	if (false) {
		cout << "Adding player with attributes: " << endl;
		cout << "Full Name: " << fullName << endl;
		cout << "Symbol: " << symbol << endl;
		cout << "Tim cups in possession: " << numTimsCup << endl;
		cout << "Money: " << amountMoney << endl;
		cout << "Current Tile: " << position << endl;
		cout << "is in tims line: " << isInTimsLine << endl;
		cout << "Turns in line: " << turnsInLine << endl;
	}

	Player *newP = new Player(fullName, symbol, numTimsCup, amountMoney, 
			position, isInTimsLine, turnsInLine, game);
	if (curPlayer == NULL) curPlayer = newP;
	game->addPlayer(newP);
	td->notifyNewPlayer(symbol);
	td->notifyMove(symbol, 0, position);
}

void Controller::loadTile(string tileLine) {
		//cout << "OK";
	istringstream iss(tileLine);
	string tileName = "";
	string ownerFN = "";
	int numImproves = 0;
	iss >> tileName;
	iss >> ownerFN;
	iss >> numImproves;
	game->updateTileInfo(tileName, ownerFN, numImproves);
	//game->updatePlayerWorth(tileName, ownerFN)
	//cout << tileName << endl;
	if (numImproves > 0) {
		//cout << "Numimporves: " << numImproves << " on " << tileName << endl;
		td->notifyImprovements(game->getTileIndex(tileName), numImproves);
	}
}

bool Controller::loadGame(istream &input, int mode) {
	if (input.fail()) return false;
	int numPlayers = 0;
	do {
		cout << "Enter the number of players: ";
		input >> numPlayers;
		if (input.fail()) {
			input.clear();
			input.ignore(1);
			cout << "Enter an integer between 2 and 8." << endl;
			continue;
		}
		if (numPlayers > MAXPLAYERS || numPlayers < 2) cerr << "Incorrect number of players." << endl;
	} while (numPlayers > MAXPLAYERS || numPlayers < 2);
	cout << "Number of players: " << numPlayers << endl;
	if (input.fail()) {
		cerr << "Reading number of players failed." << endl;
		return false;
	}
	game = new GameBoard(this);
	td = new TextView(numPlayers);
	for (int k = 0; k < numPlayers; ++k) {
		addPlayer(input, mode);
	}
	//vector <char> playerChars;
	//for (int k = 0; k < numPlayers; ++k) {
	//	playerChars.push_back(game->getPlayerAt(k)->getCharName());
	//}
	
	if (mode == LOAD || mode == LOAD_TEST) {
		//cout << " Load";
		string tileLine;
		getline(input, tileLine); // buffer
		//cout << tileLine << endl;
		for (;;) {
			if (input.eof()) break;
			getline(input, tileLine);
			//cout << tileLine << endl;
			//cout << "next" << endl;
			loadTile(tileLine);

		}
		for (int k = 0; k < numPlayers; ++k) {
			game->getPlayerAt(k)->checkMonopoly();
		}

		for (int k = 0; k < 40; ++k) {
			MonopolyTile *mptr = dynamic_cast<MonopolyTile *>(game->getTile(k));
			RentTile *rptr = dynamic_cast<RentTile *>(game->getTile(k));
			if (mptr) {
				Player *owner = mptr->getOwner();
				if ((mptr->getNumImprove() == 0) && owner) {
					if (owner->hasMonopoly(mptr->getTileName())) {
						//cout << "Previous tuition: " << mptr->getPayableAmount() << endl;
						int newTuition = mptr->getPayableAmount() * 2;
						mptr->setPayableAmount(newTuition);
						//cout << "New tuition: " << newTuition << endl;
						//cout << mptr->getTileName() << " has no improvements and monoply with tuition " << mptr->getPayableAmount() << endl;
					}
				}
			} 
			if (rptr) {
				Player *owner = rptr->getOwner();
				rptr->setPayableAmount(rptr->calculateResPayableAmount(owner));
				//cout << rptr->getTileName() << " has rent " << rptr->getPayableAmount() << endl;
			}
		} ///////////////HAVE TO CHECK MONOPOLY AND SET 

	}
	//cout << "done";
	return true;
}

bool Controller::saveGame(string fileName) {
	if (!game->saveGame(fileName, curPlayer)) return false;
	cout << "Save to " << fileName << " successful." << endl;
	return true;
}

void Controller::init(int mode) {
	if (mode == NEW_TEST || mode == LOAD_TEST) testing = true;
	
	if (mode == LOAD || mode == LOAD_TEST) {
		ifstream fs(loadFile.c_str());
		if (fs.fail()) return;
		loadGame(fs, mode);
	} else {
		loadGame(cin, mode);
	}

	// NOTIFY VIEW!!!!!!!!!!!!!!AND PRINT GAMEBOARD STATE
	td->print();
	play();
}

bool isTestingRoll(string command) {
	istringstream iss(command);
	string op;
	iss >> op;
	if (op == "roll") {
		if (iss.fail()) return false;
		int op1, op2;
		iss >> op1;
		if (iss.fail()) return false;
		iss >> op2;
		if (iss.fail()) return false;
		//cout << "IS TESTING" << endl;
		return true;
	} else {
		//cout << "IS NOT TESTING" << endl;
		return false;
	}
}
/*
bool isImproveCmd(string command) {
	istringstream iss(command);
	string op;
	iss >> op;
	if (iss.fail()) return false;
	if (op == "improve") {
		return true;
	} else {
		return false;
	}
}
*/
bool isCommand(string command, string given) {
	istringstream iss(given);
	string op;
	iss >> op;
	if (iss.fail()) return false;
	if (op == command) {
		return true;
	} else {
		return false;
	}
}

string makeGoodCmd(string orig) {
	istringstream iss(orig);
	string temp;
	string ret = "";
	iss >> skipws;
	int k = 0;
	//cout << "Roginal:" << orig << endl;
	for (;;) {
		iss >> temp;
		//cout << "temp:" << temp << endl;
		if (iss.fail()) {
			break;
		} else {
			if (k > 0) ret = ret + ' ';
			ret = ret + temp;
		}
		//ret = ret + temp;
		++k;
	}
	//cout << "Good command is:" << ret << endl;
	return ret;
}

void Controller::play() {
	string command;
	//bool rolled = false;
	//getline(cin, command);
	//cin.ignore('\n');
	for (;;) {
if (curPlayer->getRestrictedCommands() == true) {
				curPlayer->removeAndSellAssets(curPlayer,curPlayer->getOweDebtTo()); 
				cout << curPlayer->getFullName() << " is bankrupt and has lost the game." << endl;
			}
		if(curPlayer->getToDelete() == true){
			Player * temp = curPlayer;
			game->next();
			td->notifyRemovePlayer(temp->getCharName(),temp->getPos());
			delete temp;
			curPlayer->setRollsInRow(0);
			rolled = false;
			//td->print();
		}
		if(curPlayer->getMoney() > 0 && curPlayer->getRestrictedCommands() == true){
			if(curPlayer->getOweDebtTo() != NULL){
				curPlayer->setOweDebtTo(NULL);
			}
			cout << curPlayer->getFullName() << " raised enough money." << endl;
			curPlayer->setRestrictedCommands(false);
		}
		if (game->getCurrentNumPlayers() <= 1) {
			cout << game->getFirstPlayerName() << " wins!" << endl;
			//delete curPlayer;
			break; // Gameover
		}

		cout << curPlayer->getFullName() << "(" << curPlayer->getCharName() << ")'s turn." << endl;
		cout << "Enter command: ";
		//cin >> ws;
		//cin.clear();
		//cin.ignore();
		
		//cout << "command is " << command << endl;
		/*if (command == "") {
			cin.ignore();
			//continue;
		}*/
		do {
			getline(cin, command);
			command = makeGoodCmd(command);
		} while (command == "");

		if (cin.eof()) break;
		
		if (cin.fail()) {
			cerr << "CIN failed for some reason." << endl;
			return;
		}
		if (command == "quit") {
			break;
		} else if (command == "display") {
			td->print();
		//} else if (isImproveCmd(command)) {
		} else if (isCommand("improve", command)) {
			istringstream iss(command);
			string property;
			string bs;
			iss >> property;
			iss >> property;
			if (iss.fail()) continue;
			iss >> bs;
			if (iss.fail()) continue;
			if (improve(property, bs)) {
				MonopolyTile *mptr = dynamic_cast<MonopolyTile *>(game->getTile(property));
				td->notifyImprovements(game->getTileIndex(property), mptr->getNumImprove());
			}
		} else if (isTestingRoll(command)) {
			cout << "This is a testing roll. " << endl;
			if(rolled == false){
				istringstream iss(command);
				string temp;
				iss >> temp;
				int die1, die2;
				iss >> die1;
				iss >> die2;
				//if (roll(die1, die2)) {
					rolled = roll(die1, die2);
				//}				
			} else  {
				cout << "You have already rolled this turn." << endl;
			}
		} else if (command == "roll" && curPlayer->getRestrictedCommands() == false) {
			if(rolled == false){
				//cout << "Random roll" << endl;
				
				rolled = roll();
			} else  {
				cout << "You have already rolled this turn." << endl;
			}
		} else if (isCommand("trade", command)) {
			istringstream iss(command);
			string name = "";
			string give = "";
			string receive = "";
			iss >> name; // trade
			iss >> name;
			iss >> give;
			iss >> receive;
			if (!trade(name, give, receive)) cout << "Trade unsuccessful." << endl;;
		} else if (isCommand("mortgage", command)) {	
//			cout << "Please enter the building that you would like to mortgage" << endl;
			istringstream iss(command);
			string property = "";
			iss >> property; // mortgage
			iss >> property;
			if (!mortgage(property)) cout << "Mortgage of " << property << " unsuccessful." << endl;
		} else if (command == "assets") {
			td->print();
			assets();
		} else if (isCommand("unmortgage", command) && curPlayer->getRestrictedCommands() == false) {	
			istringstream iss(command);
			string property = "";
			iss >> property; // unmortgage
			iss >> property;
			if (!unmortgage(property)) cout << "Unmortgage of " << property << " unsuccessful." << endl;
		} else if (isCommand("save", command)) {	
			istringstream iss(command);
			string fileName = "";
			iss >> fileName; //save
			iss >> fileName;
			if (!saveGame(fileName)) cout << "Game save to " << fileName << " unsuccessful." << endl;
		} else if (command == "giveCup") {
			if (testing) {
				game->giveTimsCup(curPlayer);
			} else {
				cout << "Not in testing mode, command not available. Fucking pleb." << endl;
			}
		} else if(command == "next"&& curPlayer->getRestrictedCommands() == false){
				if(rolled == true){
					game->next();
					curPlayer->setRollsInRow(0);
					rolled = false;
					td->print();
				}
				else cout << "Please roll before passing on your turn." << endl;
		} else if(command == "bankrupt"){
			// this is whrer you can call the destructor for the player, also it will need to auction properties
			//remove and sell assets then swap to next player
				cout << "You can't declare bankruptcy yet. It's not your time." << endl;
		} else {
			cout << "Bad command, try again." << endl;
		}
	}
	cout << "Thanks for playing." << endl;
}

Controller::~Controller() {
	delete td;
	delete game;
}

void Controller::notify(char p, int oldPos, int newPos) {
	td->notifyMove(p,oldPos,newPos);
	td->print();
}

bool Controller::unmortgage(string property) {
	Tile *tptr = game->getTile(property);
	if (tptr) {
		PropertyTile *propptr= dynamic_cast<PropertyTile *>(tptr);
		game->unMortgageProperty(propptr, curPlayer);
	} else {
		cout << "Invalid property name." << endl;
		return false;
	}
	return true;
}

bool Controller::mortgage(string property) {
	//cout << "RUN" << endl; 
	Tile *tptr = game->getTile(property);
	if (tptr) {
		PropertyTile *propptr= dynamic_cast<PropertyTile *>(tptr);
		game->mortgageProperty(propptr, curPlayer);
	} else {
		cout << "Invalid property name." << endl;
		return false;
	}
	return true;
}

bool Controller::trade(string p2name, string give, string receive) {
	int intGive = isInt(give);
	int intReceive = isInt(receive);
	if ((intGive != -1) && (intReceive != -1)) {
		cout << "You are attempting to trade money for money with " << p2name << " and it makes no sense." << endl;
		return false;
	}
	if ((intGive == -1) && (intReceive == -1)) {
		PropertyTile *gptp = dynamic_cast<PropertyTile *>(game->getTile(give));
		PropertyTile *rptp = dynamic_cast<PropertyTile *>(game->getTile(receive));
		if (rptp && gptp) {
			game->trade(curPlayer->getFullName(), p2name, gptp, rptp);
		} else {
			cout << "Make sure tiles in trade are property tiles." << endl;
			return false;
		}
		return true;
	}
	if(intGive != -1){ // offering cash for property	
		MonopolyTile * mtp = dynamic_cast<MonopolyTile *>(game->getTile(receive));
		if(mtp){
			game->trade(curPlayer->getFullName(),p2name, intGive, mtp) ;
		}
		else{
			RentTile * rtp = dynamic_cast<RentTile *>(game->getTile(receive));
			game->trade(curPlayer->getFullName(),p2name, intGive, rtp) ;
		}
		return true;
	}
	if(intGive == -1){ // offering property for cash
		MonopolyTile * mtp = dynamic_cast<MonopolyTile *>(game->getTile(give));
		if(mtp){
			game->trade(p2name,curPlayer->getFullName(), intReceive, mtp) ;//cout << "Trade unsuccessful." << endl;
		} else{
			RentTile * rtp = dynamic_cast<RentTile *>(game->getTile(give));
			game->trade(p2name,curPlayer->getFullName(), intReceive, rtp) ;
		}
		return true;
	}
	return true;

}

bool Controller::roll(int die1, int die2) {
	if (die1 == -1 && die2 == -1) {
		return game->roll(curPlayer);
	}
	if (!testing) {
		cout << "Not in testing mode. Can't use the roll command with parameters." << endl;
		return false;
	} else {
		// Do roll sum
		return game->roll(curPlayer, die1, die2);
	}
}

void Controller::assets() {
	game->assets(curPlayer);
}

void Controller::notifyEnableRoll() {
	rolled = false;
	//cout << "Can Roll again" << endl;
}

bool Controller::improve(string property, string bs) {
	MonopolyTile *mptr = dynamic_cast<MonopolyTile *>(game->getTile(property));
	if (mptr == NULL) {
		cout << "Not a property that can be improved or property doesn't exist." << endl;
		return false;
	} else {
		if (bs == "buy") {
			game->buyImprovements(curPlayer, mptr);
			return true;
		} else if (bs == "sell"){
			game->sellImprovements(curPlayer, mptr);
			return true;
		} else {
			cout << "Either buy or sell must follow the property." << endl;
			return false;
		}
	}
}
