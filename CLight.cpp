#include "GameElements.h"
#include "ConsoleControl.h"

CLIGHT::CLIGHT() {
	mX = mY = RedTime = GreenTime = 0;
	green = false;
}

CLIGHT::CLIGHT(int x, int y) : mX(x), mY(y), green(false) {}

void CLIGHT::countDown() {
	if (RedTime >= 0) {
		RedTime--;
		if (RedTime < 0)
			green = true;
	}
	else if(GreenTime >= 0){
		GreenTime--;
		if (GreenTime < 0) 
			reset();
	}
}

void CLIGHT::set(int x, int y) {
	mX = x; mY = y;
	//Random thời gian của đèn
	
	int t = rand() % (RED_TIME + GREEN_TIME);
	if (t > RED_TIME)
		GreenTime = GREEN_TIME;
	else
		GreenTime = t;
	RedTime = t - GreenTime;
	if (RedTime <= 0)
		green = true;
}

void CLIGHT::reset() {
	RedTime = RED_TIME;
	GreenTime = GREEN_TIME;
	green = false;
}


void CLIGHT::draw() {
	GotoXY(mX, mY);

	if (!green) 
		setColor(RED_BG);	
	else 
		setColor(GREEN_BG);
	
	cout << ' ';
	setColor(BW);
}

bool CLIGHT::isGreen() {
	return green;
}