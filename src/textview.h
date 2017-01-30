#ifndef TEXTVIEW_H
#define	TEXTVIEW_H
#include "view.h"
#include <vector>

const int NUMTILESONSIDE = 11;
const int VIEWTILEWIDTH_EXCLUDE_BORDERS = 9;
const int VIEWTILEHEIGHT_EXCLUDE_BORDERS = 4;

enum {G, B, D, P, S, $, L, T};

class TextView : public View{
	char **theGrid;
	int viewGridHeight;
	int viewGridWidth;
	void replaceAt(char c, int row, int col);
	void changeTileView(char player, char newChar, int pos);
	void changeImprovements(int row, int col, int numImprove);
	public:
		//TextView(int numPlayers, std::vector <char> players);
		TextView(int numPlayers);
		void notifyMove(char p, int oldPos, int newPos);
		void notifyNewPlayer(char p);
		void notifyRemovePlayer(char p, int pos);
		void notifyImprovements(int pos, int numImprove);
		void print();
		~TextView();
};

#endif
