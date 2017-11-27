#include "GameElements.h"
#include "ConsoleControl.h"

void CDINOSAUR::draw() {
	// oo    or     oo
	//  ooo       ooo
	// Hit box from mX - 1 to mX + 2
	char c1, c2, c3;
	c1 = 219;
	c2 = 220;
	c3 = 223;
	//setColor(2);
	if (Left) {
		GotoXY(mX - 1, mY);
		cout << c2 << c1 << ' ';
		GotoXY(mX, mY + 1);
		cout << c1 << c1 << c3;
	}
	else {
		GotoXY(mX, mY);
		cout << ' ' << c1 << c2;
		GotoXY(mX - 1, mY + 1);
		cout << c3 << c1 << c1;
	}
	//setColor(15);
}

void CDINOSAUR::clear() {
	if (Left) {
		GotoXY(mX - 1, mY);
		cout << "  ";
		GotoXY(mX, mY + 1);
		cout << "   ";
	}
	else {
		GotoXY(mX + 1, mY);
		cout << "  ";
		GotoXY(mX - 1, mY + 1);
		cout << "   ";
	}
}

void CDINOSAUR::Move() {
	if (Left) {
		if (mX > 4) {
			//GotoXY(mX, mY);
			//cout << ' ';
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
			//GotoXY(mX + 1, mY);
			//cout << ' ';
			GotoXY(mX - 1, mY + 1);
			cout << ' ';
			mX++;
		}
		else {
			clear();
			mX = 4 + 1;
		}
	}
}

void CDINOSAUR::Cry() {

}

bool CDINOSAUR::isHit(int x, int y) {
	if (Left) {
		if (y == mY) {
			if (x == mX || x == mX - 1)
				return true;

		}

		if (y == mY + 1) {
			for (int i = 0;i <= 2;i++) {
				if (x == mX + i)
					return true;
			}
		}
	}

	else {
		if (y == mY) {
			if (x == mX + 1 || x == mX + 2)
				return true;

		}

		if (y == mY + 1) {
			for (int i = -1;i <= 1;i++) {
				if (x == mX + i)
					return true;
			}
		}
	}
	return false;
}