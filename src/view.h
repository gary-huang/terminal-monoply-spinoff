#ifndef VIEW_H
#define	VIEW_H
#include <string>
#include <vector>

class View{
	protected:
		int numPlayers;
		std::vector <char> players;
	public:
		//View(int numPlayers, std::vector <char> players);
		View(int numPlayers);
		// this will allow me to update the board
		virtual void notifyMove(char p, int oldPos, int newPos)= 0;
		virtual void notifyNewPlayer(char p) = 0;
		virtual void notifyRemovePlayer(char p, int pos) = 0;
		virtual void notifyImprovements(int pos, int numImprove) = 0;
		// prints the board
		virtual void print() = 0;
		virtual ~View();
};

#endif
