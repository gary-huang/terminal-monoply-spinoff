#include "gameboard.h"
#include <iostream>
#include <fstream>
#include "die.h"
#include "cups.h"
#include <string>
#include "nonpropertytile.h"
#include "propertytile.h"
#include "collectOSAP.h"
#include "goosenesting.h"
#include "slc.h"
#include "tuition.h"
#include "needleshall.h"
#include "coopfee.h"
#include "dctimsline.h"
#include "gototims.h"
#include <vector>
#include <map>
using namespace std;

void GameBoard::readTuitionData() {
	string file = "tuitiondata.txt";
	
	ifstream ifs(file.c_str());
	//if (ifs.fail()) cout << "Fail" << endl;
	
	string building = "";
	//int *val = new int [6];
	int temp;
	
	for (;;) {
		//cout << "Next: " << endl;
		if (ifs.eof()) {break;} 
		vector <int> val;
		ifs >> building;
		//cout << building << endl;
		if (ifs.eof()) {break;} 
		for (int k = 0; k < 6; ++k) {
			ifs >> temp;
			val.push_back(temp);
			//ifs >> val[k];
		}
		//tuitionTable.insert(pair<string, int *>(building, val));
		tuitionTable[building] = val;
	}

	
}
bool GameBoard::winCheck(){
	return numPlayers == 1;
}

bool GameBoard::removeCup(char p) {
	return cupsInGame->removeCup(p);
}

void GameBoard::removePlayer(Player * p){ 
	bool startShifting = false;
	for(int i = 0; i < numPlayers; i++){
		if(players[i]->getFullName() == p->getFullName()){
			// this means that you are on the player to remove
			//if(notification->curPlayer->getFullName() != players[i]->getFullName()){delete players[i];}
			//Player * temp = players[i];
			startShifting = true;
		}
		if(startShifting == true){
			if(i + 1 < numPlayers){
				players[i] = players[i+1];
			}
		}
	}
	players[numPlayers-1] = NULL;
	numPlayers--; 
	}

void GameBoard::next(){
	string player = notification->curPlayer->getFullName();
	int next = 0;
	for (int i = 0; i < numPlayers; ++i){
		if(player == players[i]->getFullName()){
			next = i+1;
		}
	}
	if(next >= numPlayers){
		next = 0;
	}
	notification->curPlayer = players[next];
	//cout << "It is now " << notification->curPlayer->getFullName() << "'s turn" << endl;
}

bool GameBoard::isSymbolInvalid(char symbol) {
	switch (symbol) {
		case 'G': case 'B': case 'D': case 'P': case 'S': case '$': case 'L': case 'T':
			return false;
		default:
			cout << "Piece must be one of G, B, D, P, S, $, L, T" << endl;
			return true;
	}
}

GameBoard::GameBoard(GameNotification *notification): numPlayers(0), notification(notification) { 
	roll1 = new Die(MINROLL, MAXROLL);
	roll2 = new Die(MINROLL, MAXROLL);
	for (int k = 0; k < MAXPLAYERS; ++k) {
		players[k] = NULL;
	}
	readTuitionData();
	cupsInGame = new Cups;
	tileGrid = new Tile *[NUMTILES];
	//Player players[MAXPLAYERS];
	tileGrid[0] = new CollectOSAP(this);
	//RentTile(std::string tileName,GameBoard * g,int buyCost,std::string payableType,int payableAmount, std::string buildingType, int numTile);
	tileGrid[1] = new MonopolyTile("Arts1", "AL",T1IMPROVECOST, 40,2,this,1);
	tileGrid[2] = new Slc(this);
	tileGrid[3] = new MonopolyTile("Arts1", "ML",T1IMPROVECOST,60,4,this,3);
	tileGrid[4] = new Tuition(this);
	tileGrid[5] = new RentTile("MKV",this,200,"Rent",25,"Residence",5);
	tileGrid[6] = new MonopolyTile("Arts2","ECH",T1IMPROVECOST,100,6,this,6);
	tileGrid[7] = new NeedlesHall(this);
	tileGrid[8] = new MonopolyTile("Arts2","PAS",T1IMPROVECOST,100,6,this,8);
	tileGrid[9] = new MonopolyTile("Arts2","HH",T1IMPROVECOST,120,8,this,9);
	tileGrid[10] = new DCTimsLine(this);
	tileGrid[11] = new MonopolyTile("Eng","RCH",T2IMPROVECOST,140,10,this,11);
	tileGrid[12] = new RentTile("PAC", this,150, "Tuition",1,"Gym",12);
	tileGrid[13] = new MonopolyTile("Eng","DWE",T2IMPROVECOST,140,10,this,13);
	tileGrid[14] = new MonopolyTile("Eng","CPH",T2IMPROVECOST,140,12,this,14);
	tileGrid[15] = new RentTile("UWP",this,200,"Rent",25,"Residence",15);
	tileGrid[16] = new MonopolyTile("Health","LHI",T2IMPROVECOST,180,14,this,16);
	tileGrid[17] = new Slc(this);
	tileGrid[18] = new MonopolyTile("Health","BMH",T2IMPROVECOST,180,14,this,18);
	tileGrid[19] = new MonopolyTile("Health","OPT",T2IMPROVECOST,200,16,this,19);
	tileGrid[20] = new GooseNesting(this);
	tileGrid[21] = new MonopolyTile("Env","EV1",T3IMPROVECOST,220,18,this,21);
	tileGrid[22] = new NeedlesHall(this);
	tileGrid[23] = new MonopolyTile("Env","EV2",T3IMPROVECOST,220,18,this,23);
	tileGrid[24] = new MonopolyTile("Env","EV3",T3IMPROVECOST,240,20,this,24);
	tileGrid[25] = new RentTile("V1",this,200,"Rent",25,"Residence",25);
	tileGrid[26] = new MonopolyTile("Sci1","PHYS",T3IMPROVECOST,260,22,this,26);
	tileGrid[27] = new MonopolyTile("Sci1","B1",T3IMPROVECOST,260,22,this,27);
	tileGrid[28] = new RentTile("CIF", this,150, "Tuition",1,"Gym",28);
	tileGrid[29] = new MonopolyTile("Sci1","B2",T3IMPROVECOST,280,24,this,29);
	tileGrid[30] = new GoToTims(this);
	tileGrid[31] = new MonopolyTile("Sci2","EIT",T4IMPROVECOST,300,26,this,31);
	tileGrid[32] = new MonopolyTile("Sci2","ESC",T4IMPROVECOST,300,26,this,32);
	tileGrid[33] = new Slc(this);
	tileGrid[34] = new MonopolyTile("Sci2","C2",T4IMPROVECOST,320,28,this,34);
	tileGrid[35] = new RentTile("REV",this,T4IMPROVECOST,"Rent",25,"Residence",35);
	tileGrid[36] = new NeedlesHall(this);
	tileGrid[37] = new MonopolyTile("Math","MC",T4IMPROVECOST,350,35,this,37);
	tileGrid[38] = new CoopFee(this);
	tileGrid[39] = new MonopolyTile("Math","DC",T4IMPROVECOST,400,50,this,39);
	
}
string GameBoard::getNameAtLoc(int loc){
	return tileGrid[loc]->getTileName();
}

int GameBoard::getCurrentNumPlayers() {
	return numPlayers;
}

string GameBoard::getFirstPlayerName() {
	return players[0]->getFullName();
}

Player *GameBoard::getPlayerAt(int index) {
	if (index < 0 || index >= numPlayers) {
		cerr << "Index out of range." << endl;
		return NULL;
	}
	return players[index];
}

Tile ** GameBoard::getTileGrid(){
	return tileGrid;
}
//void notify(Player& P,  int oldPos,  int newPos);
void GameBoard::init(){
	// this loop adds all of the players to the starting position
	for(int i = 0; i < numPlayers; i++){	
		notify(players[i]->getCharName());
	}
}

bool GameBoard::isSymbolTaken(char symbol) {
	//cout << "Num players: " << numPlayers << endl;
	for (int k = 0; k < numPlayers; ++k) {
		//if (players[k]){
		if (symbol == players[k]->getCharName()) {
			cout << "Piece already taken, choose another." << endl;
			cout << "Piece must be one of G, B, D, P, S, $, L, T" << endl;
			return true;
		}
	}
	return false;
}

bool GameBoard::addPlayer(Player *p) {
	for (int k = 0; k < MAXPLAYERS; ++k)  {
		//cout << "Index :" << k << endl;
		if (players[k] == NULL) {
			players[k] = p;
			++numPlayers;
			return true;
		}
	}
	return false;
}

void GameBoard::notify(char p){
	notification->notify(p,0,0);
}
GameBoard::~GameBoard(){
	for(int i = 0; i < 40; i++){
		delete tileGrid[i];
	}
	delete [] tileGrid;
	for (int k = 0; k < MAXPLAYERS; ++k) {
		if (players[k] != NULL) {
			delete players[k];
		}
	}
	delete roll1;
	delete roll2;
	delete cupsInGame;
}

// remember to send the char, not the whole player
void GameBoard::notify(char p,  int oldPos,  int newPos){
	notification->notify(p,oldPos,newPos);
}

// this is an overload for this function so we can decide what the rolls are]
	// Gucci roll
bool GameBoard::roll(Player * player, int froll, int sroll){
	// need to see if you roll 3 doubles in a row
	if (froll == -1 && sroll == -1) {
		roll1->roll();
		froll = roll1->getLastRoll();
		roll2->roll();
		sroll = roll2->getLastRoll();
	}
	string command;
	if (player->getTimsLine()){
		cout << "You're currently stuck in DC Tim's Line." << endl;
		if (player->getTurnsinLine() >= 2) { // Third turn in tims
			cout << "Type T to use a Tims cup, or P to pay the $50 fee to get out of Tim's Line:" << endl;
			while(cin >> command){
				if(command == "T"){
					if(!useTimsCup(player)) continue; // method to use the tims cup
					player->getOutOfTims(froll, sroll);
					player->move(froll, sroll);	
					return true;
				} else if(command == "P"){
					payfeeTims(player, 50);
					player->getOutOfTims(froll, sroll);
					player->move(froll, sroll);	
					return true;
				} else{
					cout << "Not a valid response, try again." << endl;
				}
			}
		} else { // Been in Tims for less than 3 turns
			cout << "Type T to use a Tims cup, P to pay the $50 fee to get out of Tim's Line, or D to roll the dice:" << endl;
			while(cin >> command){
				if (command == "D"){
					if (froll == sroll) {
						cout << "You rolled doubles, congratulations, you're now free from DC Tim's Line!" << endl;
						player->getOutOfTims(froll, sroll);
						//player->move(froll,sroll);
						return true;
					} else {
						cout << "Your first roll was " << froll << " and your second roll was " << sroll << "." << endl;
						cout << "You are still stuck in the DC Tims Line." << endl;
						player->setTurnsInLine(player->getTurnsinLine() + 1);
						player->setSumLastDieRoll(froll+sroll);
						return true;  
					}
				} else if(command == "T"){
					if(!useTimsCup(player)) {
						continue;
					} else {
						player->getOutOfTims(froll, sroll);
						return true;
					}
				} else if(command == "P"){
					payfeeTims(player,50);
					player->getOutOfTims(froll, sroll);
					return true;
				} else {
					cout << "Not a valid command, please try again." << endl;
				}
			}
		}
		//return true;
	} else {   // not in tims line				
		if(froll == sroll){
			player->setRollsInRow(player->getRollsInRow() + 1);
			if (player->getRollsInRow() == 3){
				player->setRollsInRow(0);
				int oldPos = player->getPos();
				player->setPos(TIMS);
				player->setTimsLine(true);
				player->setTurnsInLine(0);
				notify(player->getCharName(),oldPos,player->getPos());
				cout << "Your first roll was " << froll << " and your second roll was " << sroll << "." << endl;
				cout << "Whoops, you got 3 sets of doubles in a row, proceed to DC Tim's Line." << endl;
				return true;
			} else {
				player->move(froll, sroll);
				notification->notifyEnableRoll();
				cout <<"Congratulations, you rolled a double so you get to roll again!" << endl;	
				return false;
			}
		} else {        // not doubles
			player->move(froll, sroll);	
		}
		return true;
	}
	return true;
}

void GameBoard::payfeeTims(Player * player, int amount){ 
	if(player->changeMoney(-1*amount)){
		int oldPos = player->getPos();
		player->setPos(player->getPos() + player->getSumLastDieRoll());
		if(player->getPos() >= 40){
			player->setPos(player->getPos()-40);
			// if you arent on the collect osat tile, collect osap anyway
			if(player->getPos() != 0) player->changeMoney(200);
		}
		notify(player->getCharName(),oldPos,player->getPos());
		tileEvent(player,tileGrid[player->getPos()]);
	}
	else{
		player->declareBankrupcy();
	}
}

bool GameBoard::payfee(Player * player, int amount){
	if(player->changeMoney(-1*amount)) return true;
	else{
		return player->declareBankrupcy();
	}
}


bool GameBoard::useTimsCup(Player * player){
	// check if they own a cup, update the cup array, remove a cup
	if(player->getTimsCups() <= 0){
		cout << "No cup found, please find an alternate method." << endl;		
		return false;			
	}
	else{
		cupsInGame->useCup(player->getCharName());
		player->setTimsCups(player->getTimsCups() - 1);

		// remove them from the tims cup array & move then do last roll thing///////////////////////////////////////////
		return true;
	}
}

void GameBoard::tileEvent(Player *player, Tile * tile){
	// need to see if it is a property or if it is an event tile
	/* 
	 * these are dynamic casts. Highly coupled code. Apologies here
	 * no other way to do it without restructuring a lot of code.
	*/
	 cout << "You (" << player->getFullName() << ") are now at " << tile->getTileName() << "." << endl;
	 MonopolyTile * mtp = dynamic_cast<MonopolyTile *>(tile);
	if(mtp){
		mtp->buyEvent(player);
		return ;
	}
	RentTile * rtp = dynamic_cast<RentTile *>(tile);
	if(rtp){
		rtp->buyEvent(player);
		return ;
	}
	else{
		//other wise it it a non-property tile. Meaning that doEvent will work (its a virtual function)
		NonPropertyTile * npp = dynamic_cast<NonPropertyTile *>(tile);
		npp->doEvent(player);
		return ;
	}
}

int GameBoard::rollDie(){
	roll1->roll();
	int froll = roll1->getLastRoll();
	roll2->roll();
	int sroll = roll1->getLastRoll();
	cout << "Your first roll was " << froll << " and your second roll was " << sroll << "." << endl;
	return froll + sroll;
}

bool GameBoard::isTileTradeable(MonopolyTile *property) {
	int numImprove = property->getNumImprove();
	if(numImprove > 0){
		cout << property->getTileName() << " has improvements and can't be traded." << endl;
		return false;
	}
	else{
		string monopoly = property->getMonopolyName();
		for (int i = 0; i < 40; ++i){
			MonopolyTile * mtp = dynamic_cast<MonopolyTile *>(tileGrid[i]);
			if(mtp){
				if(mtp->getMonopolyName() == monopoly && mtp->getNumImprove() != 0){
					cout << "A property in " << property->getTileName() << "'s monopoly has improvements and can't be traded." << endl;
					return false;
				}
			}
		}
	}
	return true;
}

void GameBoard::trade(string p1,string p2, int money, MonopolyTile * property){
	Player * player1;
	Player * player2;
	for (int i = 0; i < numPlayers; ++i){
		if(players[i]->getFullName() == p1){
			player1 = players[i];
		}
		if(players[i]->getFullName() == p2){
			player2 = players[i];
		}
	}
	trade(player1,player2,money,property);
}

// wrapper to go along with the implimentation of trade renttile
void GameBoard::trade(string p1,string p2, int money, RentTile * property){
	Player * player1;
	Player * player2;
	for (int i = 0; i < numPlayers; ++i){
		if(players[i]->getFullName() == p1){
			player1 = players[i];
		}
		if(players[i]->getFullName() == p2){
			player2 = players[i];
		}
	}
	trade(player1,player2,money,property);
}

void GameBoard::trade(Player * p1, Player * p2, int money, MonopolyTile * property){
	// first check if all the improvements in the monopoly are 0
	string command = "Y";
	string command2 = "Y";
	
	bool rejectOffer = false;

	if (!isTileTradeable(property)) return;

	cout << p1->getFullName() << ": Do you agree to this trade? (Y or N)" << endl;
	cin >> command;
	if(command == "Y"){
		cout << p2->getFullName() << ": Do you agree to this trade? (Y or N)" << endl;
		cin >> command2;
	}
	else{
		rejectOffer = true;
	}
	if (command2 != "Y") rejectOffer = true;
	
	if(rejectOffer == true){
		cout << "Offer rejected, better luck next time." << endl;
		return ;
	}
	else{
		if(p1->changeMoney(-1*money)){
			property->setOwner(p1);
			p2->changeMoney(money);
			p1->addTilesOwned(getTileIndex(property->getTileName()));
			p2->removeTilesOwned(getTileIndex(property->getTileName()));
			cout << p2->getFullName() << " received " << money << " and "
			<< p1->getFullName() << " received " << property->getTileName() << endl;
		}
		else{
			if(!p1->declareBankrupcy(p2,money)){
				p1->removeAndSellAssets(p1,p2);
			}
	}
	}
}
// renttile trade
void GameBoard::trade(Player * p1, Player * p2, int money, RentTile * property){
	string command = "Y";
	string command2 = "Y";
	bool rejectOffer = false;
	cout << p1->getFullName() << ": Do you agree to this trade? (Y or N)" << endl;
	cin >> command;
	if(command == "Y"){
		cout << p2->getFullName() << ": Do you agree to this trade? (Y or N)" << endl;
		cin >> command2;
	}
	else{
		rejectOffer = true;
	}
	if (command2 != "Y") rejectOffer = true;
	
	if(rejectOffer == true){
		cout << "Offer rejected, better luck next time." << endl;
	}
	else{
		if(p1->changeMoney(-1*money)){
			property->setOwner(p1);
			p2->changeMoney(money);
			p1->addTilesOwned(getTileIndex(property->getTileName()));
			p2->removeTilesOwned(getTileIndex(property->getTileName()));
			cout << p2->getFullName() << " received " << money << " and "
			<< p1->getFullName() << " received " << property->getTileName() << endl;
		}
		else{
			if(!p1->declareBankrupcy(p2,money)){
				p1->removeAndSellAssets(p1,p2);
			}
		}
	}
}
 // Property for propertyt ttrade
void GameBoard::trade(string p1, string p2, PropertyTile *prop1, PropertyTile *prop2) {
	Player * player1;
	Player * player2;
	for (int i = 0; i < numPlayers; ++i){
		if(players[i]->getFullName() == p1){
			player1 = players[i];
		}
		if(players[i]->getFullName() == p2){
			player2 = players[i];
		}
	}
	trade(player1,player2,prop1,prop2);
}

void GameBoard::trade(Player * p1, Player * p2, PropertyTile *prop1, PropertyTile *prop2) {
	string command = "Y";
	string command2 = "Y";
	bool rejectOffer = false;
	
	MonopolyTile * mtp1 = dynamic_cast<MonopolyTile *>(prop1);
	if (mtp1) {
		if (!isTileTradeable(mtp1)) return;
	}
	MonopolyTile * mtp2 = dynamic_cast<MonopolyTile *>(prop2);
	if (mtp2) {
		if (!isTileTradeable(mtp2)) return;
	}

	cout << p1->getFullName() << ": Do you agree to this trade? (Y or N)" << endl;
	cin >> command;
	if(command == "Y"){
		cout << p2->getFullName() << ": Do you agree to this trade? (Y or N)" << endl;
		cin >> command2;
	} else{
		rejectOffer = true;
	}

	if (command2 != "Y") rejectOffer = true;
	
	if(rejectOffer == true){
		cout << "Offer rejected, better luck next time." << endl;
	} else{
		prop1->setOwner(p2);
		prop2->setOwner(p1);
		p1->addTilesOwned(getTileIndex(prop2->getTileName()));
		p1->removeTilesOwned(getTileIndex(prop1->getTileName()));
		p2->addTilesOwned(getTileIndex(prop1->getTileName()));
		p2->removeTilesOwned(getTileIndex(prop2->getTileName()));
		cout << p2->getFullName() << " received " << prop1->getTileName() << " and "
			<< p1->getFullName() << " received " << prop2->getTileName() << endl;
	}
}



Tile * GameBoard::getTile(int at){
	return tileGrid[at];
}

Tile * GameBoard::getTile(string tileName) {
	for (int k = 0; k < NUMTILES; ++k) {
		if (tileGrid[k]->getTileName() == tileName) {
			return tileGrid[k];
		}
	}
	return NULL;
}

int GameBoard::getTileIndex(string tileName) {
	for (int k = 0; k < NUMTILES; ++k) {
		if (tileGrid[k]->getTileName() == tileName) {
			return k;
		}
	}
	return -1;
}

//this auction function will ask determine who wins an action and provide them with the property
void GameBoard::auction(PropertyTile * property){
	int bid = 1;
	int numBidders = numPlayers;
	for(int i = 0; i < numPlayers; i++){
		players[i]->setInBid(true);
	}
	int curr = 0;
	while(numBidders != 1){
		if (players[curr]->getInBid() == true){
			cout << players[curr]->getFullName() << ", would you like to bid: "
			<< 	bid << " for " << property->getTileName() << "? Type Y for yes, and N for no" << endl;
			string command;
			while(cin >> command){
				if(command == "Y"){
					bid = bid + 50;
					break;
				}
				else if (command == "N"){
					players[curr]->setInBid(false);
					numBidders--;
					break;
				}
				else cout << "Not a valid command, please try again." << endl;
			}
		}
		curr++;
		if(curr == numPlayers){
			curr = 0;
		}
	}
	bid = bid -50;
	if(bid < 0) bid = 1;
	for (int i = 0; i < numPlayers; ++i){
		if (players[i]->getInBid() == true){
			string playersName = players[i]->getFullName();
			if(payfee(players[i], bid)){ 
				players[i]->addTilesOwned(getTileIndex(property->getTileName()));
				property->setOwner(players[i]);
				cout << "Congratulations, " << players[i]->getFullName() <<
				" you bought " << property->getTileName() << " for " << bid <<"$"
				<< " and now you have " << players[i]->getMoney() << "$" << endl;
			break;
		}
			else{
				cout << "Since " << playersName << " was unable to pay for the property and has dropped out, there is no winner to this auction." << endl;
			}
		}
	}
}
// make sure to pass the player pointer that is calling for it to be mortgaged
void GameBoard::mortgageProperty(PropertyTile *property, Player * player){
	if(property->getPayableType() == "Tuition"){
		// now I already know its a monopolt tile, static casting works
		MonopolyTile * mtp = dynamic_cast<MonopolyTile *>(property);
		if(mtp){ // its a monopoly tile
			int numImprove = mtp->getNumImprove();
			if(numImprove != 0){
				cout << "Please sell all improvements before you can mortgage property." << endl;
				return;
			} 
		}
	}
	if(property->getOwner()!= NULL){
 		if(property->getOwner()->getFullName() != player->getFullName()){
			cout << "You do not own this property, so you cannot mortgage it." << endl;
		}
		else if (property->getMortgaged() == true){
			cout << "Cannot mortgage multiple times." << endl;
		}
		else{
			int amount = (property->getCost()) / 2;
			cout << "Because " << property->getTileName() << " cost $" << property->getCost() << " to buy, ";
			cout << "Player " << player->getFullName() << " received $" << amount << " for mortgaging property." << endl;
			player->changeMoney(amount);
			property->setMortgaged(true);
		}
	}
	else{
		cout << "You do not own this property, so you cannot mortgage it." << endl;
	}
}

void GameBoard::unMortgageProperty(PropertyTile *property, Player * player){
	// player must pay %60 of the original cost of the property to unmortgaged
	if(property->getMortgaged() == false){
		cout << "This builing isn't mortgaged." << endl;
		return ;
	}
	int amount =  0.6 * property->getCost();
	if(player->changeMoney(-1*amount)){
		property->setMortgaged(false);
		cout << player->getFullName() << " paid $" << amount << " to unmortgage " << property->getTileName() << "." << endl;
		cout << "Building is now unmortgaged." << endl;
		return;
	}
	else{
		player->declareBankrupcy();
	}
}

Player *GameBoard::getPlayerPtr(string playerFN) {
	if (playerFN == "BANK") return NULL;
	for (int k = 0; k < numPlayers; ++k) {	
		if (players[k]->getFullName() == playerFN) return players[k];
	}
	return NULL;
}

bool GameBoard::updateTileInfo(string tileName, string ownerFN, int numImproves) {
	for (int k = 0; k < NUMTILES; ++k) {
		if (tileGrid[k] != NULL) {
			if (tileGrid[k]->getTileName() == tileName) {
				Player *owner = getPlayerPtr(ownerFN);
				//cout << "Tile Index: " << k << endl;
				//cout << "Tile Name: " << tileName << endl;
				//cout << "Tile Onwer: " << ownerFN << endl;
				//cout << "numImproves: " << numImproves << endl;
				tileGrid[k]->notifyMonoplyUpdate(owner, numImproves);
				return true;
			}
		}
	}
	return false;
}

int GameBoard::getPlayerIndex(Player *player) {
	for (int k = 0; k < MAXPLAYERS; ++k) {
		if (player == players[k]) return k;
	}
	return -1;
}

bool GameBoard::writePlayer(ofstream &ofs, Player *player) {
	if (player == NULL) cout << "NULL" << endl;
	ofs << player->getFullName() << " " << player->getCharName() << " " << player->getTimsCups();
	if (ofs.fail()) return false;
	ofs << " " << player->getMoney() << " " << player->getPos();
	if (ofs.fail()) return false;
	if (player->getPos() == TIMS) {
		ofs << " ";
		if (player->getTimsLine()) {
			ofs << "1" << " ";
			ofs << player->getTurnsinLine();
		} else {
			ofs << "0";
		}
		if (ofs.fail()) return false;
	}
	ofs << endl;
	return true;
}

bool GameBoard::writeTile(ofstream &ofs, PropertyTile *tile) {
	ofs << tile->getTileName() << " ";
	Player *owner = tile->getOwner();
	if (owner) {
	 	ofs << owner->getFullName() << " ";
	} else {
		ofs << "BANK" << " ";
	}
	if (ofs.fail()) return false;
	if (tile->getMortgaged()) {
		ofs << "-1";
	} else {
		MonopolyTile *mptptr = dynamic_cast<MonopolyTile *>(tile);
		if (mptptr) {
			ofs << mptptr->getNumImprove();
		} else { // GYM REZ tile
			ofs << "0";
		}
	}
	if (ofs.fail()) return false;
	ofs << endl;
	return true;
}

bool GameBoard::saveGame(string fileName, Player *curPlayer) {
	ofstream ofs(fileName.c_str());
	if (ofs.fail()) return false;
	ofs << numPlayers << endl;
	int curPlayerIndex = getPlayerIndex(curPlayer);
	for (int k = curPlayerIndex; k < numPlayers; ++k) {
		if (!writePlayer(ofs, players[k])) return false;
	}
	for (int k = 0; k < curPlayerIndex; ++k) {
		if (!writePlayer(ofs, players[k])) return false;
	}
	for (int k = 0; k < NUMTILES; ++k) {
		PropertyTile *propptr = dynamic_cast<PropertyTile *>(tileGrid[k]);
		if (propptr) {
			if (!writeTile(ofs, propptr)) return false;	
		}
	}
	ofs << endl;
	return true;
}


int GameBoard::getTuitionAmount(int numImproves, string tileName) {
	//int val = (tuitionTable.at(tileName));
	vector <int> v = tuitionTable.at(tileName);
	/*for (vector <int>::iterator it=v.begin(); it != v.end(); ++it){
		cout << *it << " ";
	}*/
	return v.at(numImproves);
}

void GameBoard::assets(Player *who) {
	who->printAssets();
}

bool GameBoard::giveTimsCup(Player *who) {
	bool status = cupsInGame->notifyCupReceived(who);
	if (status) {
		who->setTimsCups(who->getTimsCups() + 1);
	}
	return status;
}

void GameBoard::sellImprovements(Player * player, MonopolyTile * property){
	if(property->getOwner()->getFullName() != player->getFullName()){
		cout << "You do not own this property so you cannot sell its improvements." << endl;
		return ;
	}
	else if(getTileIndex(property->getTileName()) == -1){
		cout << "Property does not exist." << endl;
		return;
	}
	else if(property->getNumImprove() <= 0){
		cout << "This property does not have improvements." << endl;
		return;
	}
	else{ // no errors, actually sell the imrpovement
		int numImproves = property->getNumImprove();
		player->changeMoney(property->getImproveCost()/2);
		property->setNumImprove(numImproves - 1);
		cout << player->getFullName() << " received " << property->getImproveCost()/2 << "$ for selling improvement on "
		 << property->getTileName() << endl << "The property now has " << numImproves -1 << " improvements." << endl; 
	}

}

void GameBoard::buyImprovements(Player * player, MonopolyTile * property){
	string playerName = player->getFullName();
	player->checkMonopoly();
	if(!player->hasMonopoly(property->getMonopolyName())){
		cout << "You " << "(" << player->getFullName() <<")" << " do not own the " <<
		property->getMonopolyName() << " monopoly. Therefore you cannot buy an improvement." << endl;
		return;
	}
	else if(property->getNumImprove() >= 5){
		cout << "You already have 5 improvements on this tile." << endl;
		return;
	}
	else{
		if(player->changeMoney(-1 *property->getImproveCost())){
			property->setNumImprove(property->getNumImprove() + 1);
			cout << "You successfully added an improvement to " << property->getTileName() <<
			", this tile now has " << property->getNumImprove() << " improvements." << endl;
			return;
		}
		else{
			if(player->declareBankrupcy()){
				property->setNumImprove(property->getNumImprove() + 1);
				cout << "You successfully added an improvement to " << property->getTileName() <<
				", this tile now has " << property->getNumImprove() << " improvements." << endl;
				return;		
			}
			else{
				cout << playerName << " was unable to raise enough money." << endl;
			}
		}
	}
}

int GameBoard::getNumTimsCups() {
	return cupsInGame->getNumCups();
}
