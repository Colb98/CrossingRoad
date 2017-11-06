#include "GameElements.h"
#include "ConsoleControl.h"




void CCHARACTER::draw(char c, int color) {
	setColor(color);
	GotoXY(mX, mY);
	cout << c;
	setColor(15);
}

void CPEOPLE::Up() {
	if (mY > 1) {		
		GotoXY(mX, mY);
		cout << ' ';
		mY--;
	}
}

void CPEOPLE::Down() {
	if (mY < HEIGHT) {
		GotoXY(mX, mY);
		cout << ' ';
		mY++;
	}		
}

void CPEOPLE::Left() {
	if (mX > 1) {
		GotoXY(mX, mY);
		cout << ' ';
		mX--;
	}
}

void CPEOPLE::Right() {
	if (mX < WIDTH) {
		GotoXY(mX, mY);
		cout << ' ';
		mX++;
	}
}

bool CPEOPLE::isImpact(CVEHICLE** ax, int level) {
	for (int i = 0;i < INIT_CAR + INIT_TRUCK + level*16;i++)
		if (mX == ax[i]->mX && mY == ax[i]->mY) {
			this->mState = false;
			delete[] ax;
			return true;
		}
	delete[] ax;
	return false;
}

bool CPEOPLE::isImpact(CANIMAL** at, int level) {
	for (int i = 0;i < INIT_DINO + INIT_BIRD + level*16;i++)
		if (mX == at[i]->mX && mY == at[i]->mY) {
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


void CGAME::allocThings()
{
	int i;
	
	an = new CPEOPLE(WIDTH / 2, HEIGHT);

	int nCar, nTruck, nBird, nDino;
	nCar = INIT_CAR + mlevel * INC_P_LV;
	nTruck = INIT_TRUCK + mlevel * INC_P_LV;
	nBird = INIT_BIRD + mlevel * INC_P_LV;
	nDino = INIT_DINO + mlevel * INC_P_LV;


	CVEHICLE **ax = new CVEHICLE*[nCar + nTruck];
	axt = new CVEHICLE*[nTruck];
	axh = new CVEHICLE*[nCar];
	for (i = 0;i < nTruck;i++)
		axt[i] = ax[i] = new CTRUCK();
	for (i = 0;i < nCar;i++)
		axh[i] = ax[nTruck + i] = new CCAR();


	CANIMAL **at = new CANIMAL*[nDino + nBird];
	ac = new CANIMAL*[nBird];
	akl = new CANIMAL*[nDino];
	for (i = 0;i < nDino;i++)
		akl[i] = at[i] = new CDINOSAUR();
	for (i = 0;i < nBird;i++)
		ac[i] = at[nDino + i] = new CBIRD();

	delete[] at;
	delete[] ax;
}

void CGAME::deallocThings()
{
	if(an)
		delete an;
	if (akl) {
		for (int i = 0;i < INIT_DINO + mlevel * INC_P_LV;i++)
			delete akl[i];
		delete[] akl;
	}

	if (axt) {
		for (int i = 0;i < INIT_TRUCK + mlevel * INC_P_LV;i++)
			delete axt[i];
		delete[] axt;
	}
	if (axh) {
		for (int i = 0;i < INIT_CAR + mlevel * INC_P_LV;i++)
			delete axh[i];
		delete[] axh;
	}
	if (ac) {
		for (int i = 0;i < INIT_BIRD + mlevel * INC_P_LV;i++)
			delete ac[i];
		delete[] ac;
	}	
	an = NULL;
	akl = ac = NULL;
	axh = axt = NULL;
}

void CGAME::resetGame()
{
	deallocThings();
	mlevel = 0;
	allocThings();
}

CGAME::CGAME() : mlevel(0) {
}

void CGAME::drawBoard() {
	int i;

	GotoXY(0, 0);
	cout << (char)201;	
	for (i = 0;i < WIDTH;i++)
		cout << (char)205;
	cout << (char)187;

	GotoXY(0, HEIGHT + 1);
	cout << (char)200;
	for(i = 0;i<WIDTH;i++)
		cout << (char)205;
	cout << (char)188;

	for (i = 0;i < HEIGHT;i++) {
		GotoXY(0, 1 + i);
		cout << (char)186;
		GotoXY(WIDTH + 1, 1 + i);
		cout << (char)186;
	}

	GotoXY(WIDTH + 4, 10);
	cout << "Level: ";
}


void SmartDraw(CVEHICLE **a, int size) {
	bool Left;
	int i = 0, j = size / 4 - 1;
	Left = a[0]->isLeft();
	if (Left) {
		while (i < size) {
			a[i]->eraseRight();
			i += size / 4;
		}
		while (j < size) {
			a[j]->draw();
			j += size / 4;
		}
	}
	else {
		while (j < size) {
			a[j]->eraseLeft();
			j += size / 4;
		}
		while (i < size) {
			a[i]->draw();
			i += size / 4;
		}
	}
}

void SmartDraw(CANIMAL **a, int size) { //Chi ve va xoa phan tu cuoi + dau, khong xoa tat ca
	bool Left;
	int i = 0, j = size / 4 - 1;
	Left = a[0]->isLeft();
	if (Left) {
		while (i < size) {
			a[i]->eraseRight();
			i += size / 4;
		}
		while (j < size) {
			a[j]->draw();
			j += size / 4;
		}
	}
	else {
		while (j < size) {
			a[j]->eraseLeft();
			j += size / 4;
		}
		while (i < size) {
			a[i]->draw();
			i += size / 4;
		}
	}
}

void CGAME::drawFull() {
	int i;
	clearScr();
	for (i = 0;i < INIT_TRUCK + mlevel * INC_P_LV;i++)
		axt[i]->draw();
	for (i = 0;i < INIT_CAR + mlevel * INC_P_LV;i++)
		axh[i]->draw();
	for (i = 0;i < INIT_BIRD + mlevel * INC_P_LV;i++)
		ac[i]->draw();
	for (i = 0;i < INIT_TRUCK + mlevel * INC_P_LV;i++)
		akl[i]->draw();
	an->draw();
	GotoXY(WIDTH + 11, 10);
	cout << mlevel;
}

void CGAME::drawGame() {	
	SmartDraw(axt, INIT_TRUCK + mlevel * INC_P_LV);
	SmartDraw(axh, INIT_CAR + mlevel * INC_P_LV);
	SmartDraw(akl, INIT_DINO + mlevel * INC_P_LV);
	SmartDraw(ac, INIT_BIRD + mlevel * INC_P_LV);
	an->draw();
}

void CGAME::clearScr() {
	int i, j;
	for (i = 1;i <= HEIGHT;i++) {
		GotoXY(1, i);
		for (j = 0; j < WIDTH;j++)
			cout << ' ';
	}
}

CPEOPLE* CGAME::getPeople() {
	return an;
}
CVEHICLE** CGAME::getVehicle() {
	int nCar = INIT_CAR + mlevel * INC_P_LV, nTruck = INIT_TRUCK + mlevel * INC_P_LV;
	CVEHICLE **t = new CVEHICLE*[nCar + nTruck];
	for (int i = 0;i < nCar + nTruck;i++)
		if (i < nTruck)
			t[i] = axt[i];
		else
			t[i] = axh[i - nTruck];
	return t;
}

CANIMAL** CGAME::getAnimal() {
	CANIMAL **t = new CANIMAL*[INIT_BIRD + INIT_DINO + mlevel * 2 * INC_P_LV];
	for (int i = 0;i < INIT_BIRD + INIT_DINO + mlevel * 2 * INC_P_LV;i++)
		if (i < INIT_DINO + mlevel * INC_P_LV)
			t[i] = akl[i];
		else
			t[i] = ac[i - INIT_DINO - mlevel * INC_P_LV];
	return t;
}

void CGAME::startGame() {
	resetGame();
	drawBoard();
	levelUp();
	drawFull();
	GotoXY(0, HEIGHT + 5);
	for (int i = 0;i < 50;i++)
		cout << ' ';
}

void CGAME::exitGame(thread* t) {
	system("cls");
	IsRunning = false;
	t->join();
}

void CGAME::pauseGame(HANDLE t) {
	SuspendThread(t);
}

void CGAME::resumeGame(HANDLE t) {
	ResumeThread(t);
}

void CGAME::updatePosPeople(char c)
{
	switch (c) {
	case 'W': an->Up(); break;
	case 'S': an->Down(); break;
	case 'A': an->Left(); break;
	case 'D': an->Right(); break;
	}
}

void CGAME::updatePosVehicle()
{
	int i;
	for (i = 0;i < INIT_TRUCK + mlevel * INC_P_LV;i++)
		axt[i]->Move();
	for (i = 0;i < INIT_CAR + mlevel * INC_P_LV;i++)
		axh[i]->Move();
}

void CGAME::updatePosAnimal()
{
	int i;
	for (i = 0;i < INIT_DINO + mlevel * INC_P_LV;i++)
		akl[i]->Move();
	for (i = 0;i < INIT_BIRD + mlevel * INC_P_LV;i++)
		ac[i]->Move();
}

CGAME::~CGAME() {
	deallocThings();
}

void CGAME::levelUp() {
	deallocThings();
	mlevel++;
	allocThings();
	srand(time(NULL));
	int rTruck, rBird, rDino, rCar; //rows num
	rTruck = rand() % 4;
	do {
		rCar = rand() % 4;
	} while (rCar == rTruck);
	do {
		rBird = rand() % 4;
	} while (rBird == rCar || rBird == rTruck);
	rDino = 6 - rCar - rBird - rTruck;

	rDino += 2;
	rCar += 2;
	rBird += 2;
	rTruck += 2;


	int x, y;
	//set Dino pos
	x = rand() % WIDTH + 1;
	for (int i = 0;i < INIT_DINO + mlevel * INC_P_LV;i++) {		
		akl[i]->Set(x--, rDino + 4*(i*4/(INIT_DINO + mlevel * INC_P_LV)));
		if (x < 1)
			x = WIDTH;
		akl[i]->setDir((rDino + 4 * (i * 4 / (INIT_DINO + mlevel * INC_P_LV))) % 2);
	}

	//set Bird, truck, car pos
	x = rand() % WIDTH + 1;
	for (int i = 0;i < INIT_BIRD + mlevel * INC_P_LV;i++) {
		ac[i]->Set(x--, rBird + 4*(i * 4 / (INIT_BIRD + mlevel * INC_P_LV)));
		if (x < 1)
			x = WIDTH;
		ac[i]->setDir((rBird + 4 * (i * 4 / (INIT_BIRD + mlevel * INC_P_LV))) % 2);
	}

	x = rand() % WIDTH + 1;
	for (int i = 0;i < INIT_CAR + mlevel * INC_P_LV;i++) {
		axh[i]->Set(x--, rCar + 4*(i * 4 / (INIT_CAR + mlevel * INC_P_LV)));
		if (x < 1)
			x = WIDTH;
		axh[i]->setDir((rCar + 4 * (i * 4 / (INIT_CAR + mlevel * INC_P_LV))) % 2);
	}

	x = rand() % WIDTH + 1;
	for (int i = 0;i < INIT_TRUCK + mlevel * INC_P_LV;i++) {
		axt[i]->Set(x--, rTruck + 4*(i * 4 / (INIT_TRUCK + mlevel * INC_P_LV)));
		if (x < 1)
			x = WIDTH;
		axt[i]->setDir((rTruck + 4 * (i * 4 / (INIT_TRUCK + mlevel * INC_P_LV))) % 2);
	}

	drawFull();
}