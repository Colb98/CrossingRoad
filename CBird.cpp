#include "GameElements.h"
#include "ConsoleControl.h"

void CBIRD::draw() {
	//oo__oo
	//  oo
	//hit box from mX - 2 to mX + 3
	char c1, c2;
	c1 = 220;
	c2 = 223;
	//setColor(9);
	GotoXY(mX - 2, mY);
	cout << c1 << c1 << "  " << c1 << c1;
	GotoXY(mX, mY + 1);
	cout << c2 << c2;
	//setColor(15);
}

void CBIRD::clear() {
	GotoXY(mX - 2, mY);
	cout << "      ";
	GotoXY(mX, mY + 1);
	cout << "  ";
}

void CBIRD::Move() {
	
	if (Left) {
		if (mX > 4) {
			GotoXY(mX + 3, mY);
			cout << ' ';
			GotoXY(mX + 1, mY + 1);
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
			GotoXY(mX - 2, mY);
			cout << ' ';
			GotoXY(mX, mY + 1);
			cout << ' ';
			mX++;
		}
		else {
			clear();
			mX = 4 + 1;
		}
	}
}

void CBIRD::Cry() {

}

bool CBIRD::isHit(int x, int y) {
	if (y == mY) {
		for (int i = -2;i <= 3;i++) {
			if (x == mX + i)
				return true;
		}
	}

	if (y == mY + 1) {
		if (x == mX || x == mX + 1)
			return true;
	}

	return false;
}