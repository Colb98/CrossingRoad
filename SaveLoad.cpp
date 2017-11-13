#include <fstream>
#include "GameElements.h"




ostream& operator << (ostream& os, const CCHARACTER& c) {
	int x, y;
	c.get(x, y);
	os << x << ' ' << y << endl;
	return os;
}

istream& operator>>(istream& is, CCHARACTER& c) {
	int x, y;
	is >> x >> y;
	if (x<1 || x>WIDTH)
		x = WIDTH;
	c.Set(x, y);
	return is;
}

bool CGAME::saveGame(ostream& os) {
	if (!os.good())
		return false;
	os << mlevel << endl;
	os << *akl[0] << *ac[0] << *axt[0] << *axh[0] << *an;	
	return true;
}

bool CGAME::loadGame(istream& is) {
	deallocThings();
	is >> mlevel;	
	allocThings();
	drawBoard();
	
	is >> *akl[0] >> *ac[0] >> *axt[0] >> *axh[0] >> *an;
	
	if (!legalSave())
		return false;
	
	setPosDir();
	drawFull();
	return true;
}

bool CGAME::legalSave() {
	int x[5], y[5], i, j, k;
	akl[0]->get(x[0], y[0]);
	ac[0]->get(x[1], y[1]);
	axt[0]->get(x[2], y[2]);
	axh[0]->get(x[3], y[3]);
	an->get(x[4], y[4]);

	//Vuot ngoai khung
	for (i = 0;i < 5;i++)
		if (y[i]<2 || y[i]> HEIGHT)
			return false;


	//2 hang xe trung nhau
	for (i = 0;i < 3;i++)
		for (j = i + 1;j < 4;j++)
			for(k=0;k<DISTANCE_LANE;k++)
				if(y[i]==y[j]+k || y[i]==y[j]-k)
					return false;

	return true;
}

void CGAME::resetSave(ostream &os) {
	resetGame();
	levelUp(false);
	saveGame(os);
	deallocThings();
}