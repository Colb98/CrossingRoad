#include "GameElements.h"
#include "ConsoleControl.h"






void CCHARACTER::Set(int x, int y) {
	mX = x;
	mY = y;
}





void CGAME::allocThings()
{
	int i;
	
	an = new CPEOPLE(WIDTH / 2, HEIGHT - 1);

	int nCar, nTruck, nBird, nDino;
	nCar = INIT_CAR + mlevel * INC_P_LV;
	nTruck = INIT_TRUCK + mlevel * INC_P_LV;
	nBird = INIT_BIRD + mlevel * INC_P_LV;
	nDino = INIT_DINO + mlevel * INC_P_LV;

	//Tạo mảng xe trừu tượng -> lưu vào xe tải và xe hơi 
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

	//INIT TRAFIC LIGHTS
	al = new CLIGHT[NUM_OF_LANE*2];
}

void CGAME::deallocThings()
{
	if (al)
		delete[] al;

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
	al = NULL;
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


//void SmartDraw(CVEHICLE **a, int size) {
//	bool Left;
//	int i = 0, j = size / NUM_OF_LANE - 1;
//	Left = a[0]->isLeft();
//	if (Left) {
//		while (i < size) {
//			//a[i]->eraseRight();
//			i += size / NUM_OF_LANE;
//		}
//		while (j < size) {
//			a[j]->draw();
//			j += size / NUM_OF_LANE;
//		}
//	}
//	else {
//		while (j < size) {
//			//a[j]->eraseLeft();
//			j += size / NUM_OF_LANE;
//		}
//		while (i < size) {
//			a[i]->draw();
//			i += size / NUM_OF_LANE;
//		}
//	}
//}
//
//void SmartDraw(CANIMAL **a, int size) { //Chi ve va xoa phan tu cuoi + dau, khong xoa tat ca
//	bool Left;
//	int i = 0, j = size / NUM_OF_LANE - 1;
//	Left = a[0]->isLeft();
//	if (Left) {
//		while (i < size) {
//			//a[i]->eraseRight();
//			i += size / NUM_OF_LANE;
//		}
//		while (j < size) {
//			a[j]->draw();
//			j += size / NUM_OF_LANE;
//		}
//	}
//	else {
//		while (j < size) {
//			//a[j]->eraseLeft();
//			j += size / NUM_OF_LANE;
//		}
//		while (i < size) {
//			a[i]->draw();
//			i += size / NUM_OF_LANE;
//		}
//	}
//}

void CGAME::drawFull() {
	int i;
	clearScr();
	drawBoard();

	setColor(6);
	for (i = 0;i < INIT_TRUCK + mlevel * INC_P_LV;i++)
		axt[i]->draw();

	setColor(7);
	for (i = 0;i < INIT_CAR + mlevel * INC_P_LV;i++)
		axh[i]->draw();

	setColor(9);
	for (i = 0;i < INIT_BIRD + mlevel * INC_P_LV;i++)
		ac[i]->draw();

	setColor(2);
	for (i = 0;i < INIT_DINO + mlevel * INC_P_LV;i++)
		akl[i]->draw();

	setColor(15);
	an->draw();
	GotoXY(WIDTH + 11, 10);
	cout << mlevel;
}

void CGAME::drawGame() {	
	//SmartDraw(axt, INIT_TRUCK + mlevel * INC_P_LV);
	//SmartDraw(axh, INIT_CAR + mlevel * INC_P_LV);
	//SmartDraw(akl, INIT_DINO + mlevel * INC_P_LV);
	//SmartDraw(ac, INIT_BIRD + mlevel * INC_P_LV);
	int i;
	setColor(6);
	for (i = 0;i < INIT_TRUCK + mlevel * INC_P_LV;i++)
		axt[i]->draw();
	
	setColor(7);
	for (i = 0;i < INIT_CAR + mlevel * INC_P_LV;i++)
		axh[i]->draw();

	setColor(9);
	for (i = 0;i < INIT_BIRD + mlevel * INC_P_LV;i++)
		ac[i]->draw();

	setColor(2);
	for (i = 0;i < INIT_DINO + mlevel * INC_P_LV;i++)
		akl[i]->draw();
	drawLight();
	//an->draw();
}

void CGAME::drawLight() {
	for (int i = 0;i < NUM_OF_LANE * 2;i++)
		al[i].draw();
}

void CGAME::clearScr() {
	//int i, j;
	//for (i = 1;i <= HEIGHT;i++) {
	//	GotoXY(1, i);
	//	for (j = 0; j < WIDTH;j++)
	//		cout << ' ';
	//}
	ClearScreen();
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
	default: return;
	}
	an->draw();
}

void CGAME::updatePosVehicle()
{
	int i;
	for (i = 0;i < INIT_CAR + mlevel * INC_P_LV;i++)
		if (al[i / ((INIT_CAR + mlevel * INC_P_LV) / NUM_OF_LANE)].isGreen())
			axh[i]->Move();

	for (i = 0;i < INIT_TRUCK + mlevel * INC_P_LV;i++)
		if (al[2 + i / ((INIT_TRUCK + mlevel * INC_P_LV) / NUM_OF_LANE)].isGreen())
			axt[i]->Move();

	for (int i = 0;i < NUM_OF_LANE * 2;i++)
		al[i].countDown();
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

void CGAME::levelUp(bool isDraw) {
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

	//Cách thưa các làn xe
	rDino *= DISTANCE_LANE;
	rCar *= DISTANCE_LANE;
	rBird *= DISTANCE_LANE;
	rTruck *= DISTANCE_LANE;

	//Cách so với lề trên
	rDino += 2;
	rCar += 2;
	rBird += 2;
	rTruck += 2;


	int x, y;
	//random hoành độ, cách xa biên
	x = rand() % (WIDTH - 12) + 7;
	akl[0]->Set(x, rDino);
	x = rand() % (WIDTH - 12) + 7;
	ac[0]->Set(x, rBird);
	x = rand() % (WIDTH - 12) + 7;
	axt[0]->Set(x, rTruck);
	x = rand() % (WIDTH - 12) + 7;
	axh[0]->Set(x, rCar);

	setPosDir();

	if(isDraw)
		drawFull();
}

void CGAME::setPosDir() {
	//set data
	int x, y;
	int xx;
	int distance; //Khoảng cách giữa các xe, thú
	distance = WIDTH / ((INIT_DINO + mlevel*INC_P_LV)/2) - 2;
	akl[0]->get(x, y);
	//Cái đống trong ngoặc: (i*NUM_OF_LANE/(INIT_...) là dòng thứ k của loài đó
	for (int i = 0;i < INIT_DINO + mlevel * INC_P_LV;i++) {
		if (x < 4)
			x = WIDTH - 4 - 1 - (4 - x);
		akl[i]->Set(x, y + NUM_OF_OBJ*(i * NUM_OF_LANE / (INIT_DINO + mlevel * INC_P_LV)));

		akl[i]->setDir();
		x -= distance;
	}

	//set Bird, truck, car pos
	ac[0]->get(x, y);
	for (int i = 0;i < INIT_BIRD + mlevel * INC_P_LV;i++) {
		if (x < 4)
			x = WIDTH - 4 - 1 - (4 - x);
		ac[i]->Set(x, y + NUM_OF_OBJ*(i * NUM_OF_LANE / (INIT_BIRD + mlevel * INC_P_LV)));

		ac[i]->setDir();	
		x -= distance;
	}

	//đối với xe tải và xe hơi, lấy thêm vị trí hàng để đặt đèn xanh đỏ
	axh[0]->get(x, y);	
	for (int i = 0;i < INIT_CAR + mlevel * INC_P_LV;i++) {
		if (x < 4)
			x = WIDTH - 4 - 1 - (4 - x);
		axh[i]->Set(x, y + NUM_OF_OBJ*(i * NUM_OF_LANE / (INIT_CAR + mlevel * INC_P_LV)));

		axh[i]->setDir();	
		x -= distance;
	}

	//Trafic light
	srand(time(NULL));
	for (int i = 0; i < NUM_OF_LANE; i++) {		
		if (axh[0]->isLeft()) 
			xx = 1;
		else
			xx = WIDTH;
		al[i].set(xx, y + NUM_OF_OBJ*i);
	}


	axt[0]->get(x, y);
	for (int i = 0;i < INIT_TRUCK + mlevel * INC_P_LV;i++) {
		if (x < 4)
			x = WIDTH - 4 - 1 - (4 - x);
		axt[i]->Set(x, y + NUM_OF_OBJ*(i * NUM_OF_LANE / (INIT_TRUCK + mlevel * INC_P_LV)));

		axt[i]->setDir();	
		x -= distance;
	}
	
	//Trafic light
	srand(time(NULL));
	for (int i = 0; i < NUM_OF_LANE; i++) {
		if (axt[0]->isLeft())
			xx = 1;
		else
			xx = WIDTH;
		al[i + NUM_OF_LANE].set(xx, y + NUM_OF_OBJ*i);
	}
}


//
//for (int i = 0;i < INIT_DINO + mlevel * INC_P_LV;i++) {		
//	akl[i]->Set(x--, rDino + NUM_OF_OBJ*(i * NUM_OF_LANE/(INIT_DINO + mlevel * INC_P_LV))); 
//	if (x < 1)
//		x = WIDTH;
//	akl[i]->setDir();
//	//akl[i]->setDir((rDino + NUM_OF_OBJ * (i * NUM_OF_LANE / (INIT_DINO + mlevel * INC_P_LV))) % 2);
//}
////set Bird, truck, car pos
//x = rand() % WIDTH + 1;
//for (int i = 0;i < INIT_BIRD + mlevel * INC_P_LV;i++) {
//	ac[i]->Set(x--, rBird + NUM_OF_OBJ*(i * NUM_OF_LANE / (INIT_BIRD + mlevel * INC_P_LV)));
//	if (x < 1)
//		x = WIDTH;
//	ac[i]->setDir();
//	//ac[i]->setDir((rBird + NUM_OF_OBJ * (i * NUM_OF_LANE / (INIT_BIRD + mlevel * INC_P_LV))) % 2);
//}
//x = rand() % WIDTH + 1;
//for (int i = 0;i < INIT_CAR + mlevel * INC_P_LV;i++) {
//	axh[i]->Set(x--, rCar + NUM_OF_OBJ*(i * NUM_OF_LANE / (INIT_CAR + mlevel * INC_P_LV)));
//	if (x < 1)
//		x = WIDTH;
//	axh[i]->setDir();
//	//axh[i]->setDir((rCar + NUM_OF_OBJ * (i * NUM_OF_LANE / (INIT_CAR + mlevel * INC_P_LV))) % 2);
//}
//x = rand() % WIDTH + 1;
//for (int i = 0;i < INIT_TRUCK + mlevel * INC_P_LV;i++) {
//	axt[i]->Set(x--, rTruck + NUM_OF_OBJ*(i * NUM_OF_LANE / (INIT_TRUCK + mlevel * INC_P_LV)));
//	if (x < 1)
//		x = WIDTH;
//	axt[i]->setDir();
//	//axt[i]->setDir((rTruck + NUM_OF_OBJ * (i * NUM_OF_LANE / (INIT_TRUCK + mlevel * INC_P_LV))) % 2);
//}
