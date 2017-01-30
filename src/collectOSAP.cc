#include "collectOSAP.h"
#include "player.h"
#include "gameboard.h"
using namespace std;
void CollectOSAP::doEvent(Player *player){
	player->changeMoney(200);
	cout << "You collect $200 in OSAP funds." << endl;
}
CollectOSAP::CollectOSAP(GameBoard *gameboard): NonPropertyTile(gameboard,"Collect OSAP"){}

CollectOSAP::~CollectOSAP(){}
