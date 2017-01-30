#include <iostream>
#include "cups.h"
using namespace std;

Cups::Cups(): numCups(0) {
	for (int k = 0; k < MAXCUPS; ++k) {
		playersWithCups[k] = NULL;
	}
}

int Cups::getNumCups() {
	return numCups;
}

bool Cups::notifyCupReceived(Player *p) {
	if (numCups >= MAXCUPS) {
		cout << "There are already 4 Tim's Cups!" << endl;
		return false;
	} else {
		playersWithCups[numCups] = p;
		cout << p->getFullName() << " (" << p->getCharName() << ")";
		cout << " has just received a Tim's Cup!" << endl;
		++numCups;
		return true;
	}
}

bool Cups::removeCup(char playerChar) {
	for (int k = 0; k < MAXCUPS; ++k) {
		if (playersWithCups[k]->getCharName() == playerChar) {
			playersWithCups[k] = NULL;
			// Move up rest of the player array.
			for (int j = k + 1; j < MAXCUPS; ++j) {
				playersWithCups[j - 1] = playersWithCups[j];
				playersWithCups[j] = NULL;
			}
			--numCups;
			return true;
		}
	}
	return false;
}

bool Cups::useCup(char playerChar) {
	bool status = removeCup(playerChar);
	if (status) {
		cout << playerChar << " used a Tim's Cup and is now out of Tim's line." << endl;
	} else  {
		cout << "No Tim's cups found for player " << playerChar << "." << endl;
	}
	return status;
}

Cups::~Cups() {
	for (int k = 0; k < MAXCUPS; ++k) {
		playersWithCups[k] = NULL;
	}
}
