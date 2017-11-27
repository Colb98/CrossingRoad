#include "GameElements.h"
#include "ConsoleControl.h"

void CPEOPLE::draw() {
	GotoXY(mX, mY);
	cout << 'o';
	GotoXY(mX, mY + 1);
	cout << 'Y';
}

void CPEOPLE::Up() {
	if (mY > 1) {
		GotoXY(mX, mY);
		cout << ' ';
		GotoXY(mX, mY + 1);
		cout << ' ';
		mY--;
	}
}

void CPEOPLE::Down() {
	if (mY < HEIGHT - 1) {
		GotoXY(mX, mY);
		cout << ' ';
		GotoXY(mX, mY + 1);
		cout << ' ';
		mY++;
	}
}

void CPEOPLE::Left() {
	if (mX > 3) {
		GotoXY(mX, mY);
		cout << ' ';
		GotoXY(mX, mY + 1);
		cout << ' ';
		mX--;
	}
}

void CPEOPLE::Right() {
	if (mX < WIDTH - 3) {
		GotoXY(mX, mY);
		cout << ' ';
		GotoXY(mX, mY + 1);
		cout << ' ';
		mX++;
	}
}

bool CPEOPLE::isImpact(CVEHICLE** ax, int level) {
	for (int i = 0;i < INIT_CAR + INIT_TRUCK + level*INC_P_LV * 2;i++)
		if (ax[i]->isHit(mX,mY) || ax[i]->isHit(mX,mY+1)) {
			this->mState = false;
			delete[] ax;
			return true;
		}
	delete[] ax;
	return false;
}

bool CPEOPLE::isImpact(CANIMAL** at, int level) {
	for (int i = 0;i < INIT_DINO + INIT_BIRD + level*INC_P_LV * 2;i++)
		if (at[i]->isHit(mX,mY) || at[i]->isHit(mX,mY+1)) {
			this->mState = false;
			delete[] at;
			return true;
		}
	delete[] at;
	return false;
}

bool CPEOPLE::isFinish() {
	return (mY == 1);
}

bool CPEOPLE::isDead() {
	return !mState;
}