#ifndef DIE_H
#define DIE_H

class Die {
	const int minVal;
	const int maxVal;
	int lastRoll;
	public:
		Die(const int minVal, const int maxVal);
		//~Die();
		int getLastRoll();
		int roll();
};

// Example of Die array initialization:
//Die dice[2] = {Die(1,6), Die(1,6)};

#endif
