#ifndef CUPS_H
#define CUPS_H

#include "player.h"

const int MAXCUPS = 4;

class Cups {
	int numCups;
	Player *playersWithCups[MAXCUPS];
	public:
		Cups();
		int getNumCups();
		bool notifyCupReceived(Player *p);
		bool removeCup(char playerChar);
		bool useCup(char playerChar);
		// if p2 is NULL, we will just remove the cup. will come back to this, need to shift the array
		//void transferPlayerCup(Player *player, Player player2);
		~Cups();
};

#endif
