#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>
#include <iostream>

class GameBoard;
class Player;
class TextView;

enum {NEW, LOAD, NEW_TEST, LOAD_TEST, ERR_TOO_FEW_ARGS, ERR_TOO_MANY_ARGS, ERR_INCORRECT_ARGS, ERR_FILE_FAIL};

class GameNotification {
	protected:
		
	public:
		// the controller is going to need a pointer to the current player
		Player *curPlayer;
		GameNotification();
		~GameNotification();
		virtual void notify(char p, int oldPos, int newPos) = 0;
		virtual void notifyEnableRoll() = 0;
};

class Controller: public GameNotification {
	TextView *td;
	GameBoard *game;
	std::string loadFile;
	bool testing;
	bool rolled;
	// controller will need to know who is currently going
	void addPlayer(std::istream &input, int mode);
	public:
		Controller(std::string loadFile);
		~Controller();
		void init(int mode);
		void play();
		void loadTile(std::string tileLine);
		bool loadGame(std::istream &input, int mode);
		bool saveGame(std::string fileName);
		//void roll();
		bool roll(int die1 = -1, int die2 = -1);
		void next();
		bool trade(std::string name, std::string give, std::string receive);
		bool improve(std::string property, std::string bs);
		bool mortgage(std::string property);
		bool unmortgage(std::string property);
		void bankrupt();
		void assets();
		bool save(std::string fileName);
		void notify(char p, int oldPos, int newPos);
		void notifyEnableRoll();
};

#endif
