#include <cstdlib>
#include <ctime>
#include "die.h"
using namespace std;

// Constructor using given paramters minVal as the minimum value of the die, maxVal as the 
// maximum value of the die.
Die::Die(const int minVal, const int maxVal): minVal(minVal), 
							maxVal(maxVal), lastRoll(minVal - 1) {srand(time(NULL));}

// int Die::getLastRoll() returns the last roll, if the die has never been rolled,
//	the minimum value of the die minus 1 will be returned.
int Die::getLastRoll() {
	return lastRoll;
}

// int Die::roll() returns a random value between minVal and maxVal, and saves as the last roll.
int Die::roll() {
	int ret = rand() % maxVal + minVal;
	lastRoll = ret;
	return ret;
}

