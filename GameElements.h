#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <Windows.h>
#include "ConsoleControl.h"

#define INIT_CAR 80
#define INIT_TRUCK 80
#define INIT_BIRD 100
#define INIT_DINO 100
#define MAX_LEVEL 3
#define WIDTH 85
#define HEIGHT 20
#define BASE_SPD 100
#define INC_P_LV 16

using namespace std;


class CCHARACTER {
protected:
	int mX, mY;
public:
	CCHARACTER(int x, int y) : mX(x), mY(y) {}
	void draw(char, int);
	void eraseLeft() {   //Xoa ben trai
		if (mX != 1)
			GotoXY(mX - 1, mY);
		else     //Neu ben trai la canh cua board thi xoa o sat canh phai
			GotoXY(WIDTH, mY);
		cout << ' ';
	}
	void eraseRight() {
		if (mX != WIDTH)
			GotoXY(mX + 1, mY);
		else  //Neu ben phai la canh cua board thi xoa o sat canh trai 
			GotoXY(1, mY);
		cout << ' ';
	}
};


class CVEHICLE : public CCHARACTER {
protected:
	bool Left;
public:
	CVEHICLE() : CCHARACTER(0, 0) {}
	CVEHICLE(int x, int y) : CCHARACTER(x,y) {}
	virtual void Set(int, int) = 0;
	virtual void Move() = 0;
	void setDir(bool l) {
		Left = l;
	}
	bool isLeft() {
		return Left;
	}
	friend class CPEOPLE;
	virtual void draw() = 0;
	void draw(char c, int color) {
		CCHARACTER::draw(c, color);
	}
};

class CTRUCK : public CVEHICLE {
	
public:
	CTRUCK(int x, int y) : CVEHICLE(x, y) {}
	CTRUCK() : CVEHICLE(0, 0) {}
	void Set(int x, int y) {
		mX = x;
		mY = y;
	}
	void Move() {
		int d = 1;
		if (Left)
			d = -1;
		mX += d;
		if (mX > WIDTH)
			mX = 1;
		if (mX < 1)
			mX = WIDTH;
	}
	void draw() {
		CVEHICLE::draw('t', 14);
	}
};

class CCAR : public CVEHICLE {
public:
	CCAR(int x, int y) : CVEHICLE(x, y) {}
	CCAR() : CVEHICLE(0, 0) {}
	void Set(int x, int y) {
		mX = x;
		mY = y;
	}
	void Move() {
		int d = 1;
		if (Left)
			d = -1;
		mX += d;
		if (mX > WIDTH)
			mX = 1;
		if (mX < 1)
			mX = WIDTH;
	}
	void draw() {
		CVEHICLE::draw('h', 10);
	}
};

class CANIMAL : public CCHARACTER {
protected:
	bool Left;
public:
	CANIMAL() : CCHARACTER(0,0) {}
	CANIMAL(int x, int y) : CCHARACTER(x,y) {}
	virtual void Set(int, int) = 0;
	virtual void Cry() = 0;
	virtual void Move() = 0;
	bool isLeft() {
		return Left;
	}
	void setDir(bool l) {
		Left = l;
	}
	friend class CPEOPLE;
	virtual void draw() = 0;
	void draw(char c, int color) {
		CCHARACTER::draw(c, color);
	}
};

class CDINOSAUR : public CANIMAL {
public:
	CDINOSAUR(int x, int y) : CANIMAL(x, y) {}
	CDINOSAUR() : CANIMAL(0, 0) {}
	void Set(int x, int y) {
		mX = x;
		mY = y;
	}
	void Move() {
		int d = 1;
		if (Left)
			d = -1;
		mX += d;
		if (mX > WIDTH)
			mX = 1;
		if (mX < 1)
			mX = WIDTH;
	}
	void Cry() {}
	void draw(){
		CANIMAL::draw('k', 11);
	}
};

class CBIRD :public CANIMAL {
public:
	CBIRD(int x, int y) : CANIMAL(x, y) {}
	CBIRD() : CANIMAL(0, 0) {}
	void Set(int x, int y) {
		mX = x;
		mY = y;
	}
	void Move() {
		int d = 1;
		if (Left)
			d = -1;
		mX += d;
		if (mX > WIDTH)
			mX = 1;
		if (mX < 1)
			mX = WIDTH;
	}
	void Cry() {}
	void draw() {
		CANIMAL::draw('c', 9);
	}
};

class CPEOPLE : protected CCHARACTER {
	bool mState = true;
public:
	CPEOPLE() : CCHARACTER(0, 0) {}
	CPEOPLE(int x, int y) : CCHARACTER(x, y) {}
	void Up();
	void Down();
	void Left();
	void Right();
	bool isImpact(CVEHICLE**, int);
	bool isImpact(CANIMAL**, int);
	bool isFinish();
	bool isDead();
	void draw() {
		CCHARACTER::draw('Y', 15);
	}
};

class CGAME {
	CVEHICLE **axt;
	CVEHICLE **axh;
	CANIMAL **akl;
	CANIMAL **ac;
	CPEOPLE* an;
	int mlevel;
public:
	bool IsRunning = true;
	CGAME(); //Khoi tao du lieu cac doi tuong
	void levelUp();
	int level() { return mlevel; }
	void drawBoard(); //Ve khung
	void drawGame(); //Ve tro choi
	void drawFull();
	void clearScr();
	~CGAME(); //Thu hoi bo nho
	CPEOPLE* getPeople(); //Lay thong tin nguoi
	CVEHICLE** getVehicle(); //Lay danh sach xe
	CANIMAL** getAnimal(); //Lay danh sach thu
	void allocThings();
	void deallocThings();
	void resetGame(); //Reset
	void exitGame(thread*); //Thoat thread
	void startGame(); //Start
	void loadGame(istream); //Load game
	void saveGame(ostream); //Save game
	void pauseGame(HANDLE); //Pause thread
	void resumeGame(HANDLE); //Resume thread
	void updatePosPeople(char);//Dieu khien CPEOPLE de di chuyen
	void updatePosVehicle(); //cho xe di chuyen
	void updatePosAnimal(); //Cho dong vat di chuyen
};