#include "GameElements.h"
#include "ConsoleControl.h"

void CCAR::draw() {
	// ooo
	//ooooo
	//Hit box from mX - 2 -> mX + 2
	char c1, c2, c3;
	c1 = 220; //ascii char
	c2 = 223; 	
	c3 = 'o';
	//setColor(7);
	GotoXY(mX - 1, mY);
	cout << c1 << c1 << c1;
	GotoXY(mX - 2, mY + 1);
	cout << c2 << c3 << c2 << c3 << c2;
	//setColor(15);
}

void CCAR::clear() {
	GotoXY(mX - 1, mY);
	cout << "   ";
	GotoXY(mX - 2, mY + 1);
	cout << "     ";
}

void CCAR::Move() {
	if (Left) {
		if (mX > 4) {
			GotoXY(mX + 1, mY);
			cout << ' ';
			GotoXY(mX + 2, mY + 1);
			cout << ' ';
			mX--;
		}
		else {
			clear();
			mX = WIDTH - 4 - 1;
		}
	}
	else {
		if (mX < WIDTH - 4) {
			GotoXY(mX - 1, mY);
			cout << ' ';
			GotoXY(mX - 2, mY + 1);
			cout << ' ';
			mX++;
		}
		else {
			clear();
			mX = 4 + 1;
		}
	}
}

bool CCAR::isHit(int x, int y) {
	if (y == mY || y == mY + 1) {
		for (int i = -1;i <= 1;i++) {
			if (x == mX + i)
				return true;
		}
	}

	if (y == mY + 1) {
		if (x == mX - 2 || x == mX + 2)
			return true;
	}

	return false;
}