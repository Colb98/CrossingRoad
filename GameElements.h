﻿#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <Windows.h>
#include "ConsoleControl.h"

#define INIT_CAR 6
#define INIT_TRUCK 6
#define INIT_BIRD 8
#define INIT_DINO 8
#define MAX_LEVEL 5
#define WIDTH 85
#define HEIGHT 26
#define BASE_SPD 100
#define INC_P_LV 2 // Số xe mỗi loại tăng sau khi lên lv. nên là số chẵn
#define DISTANCE_LANE 3
#define NUM_OF_LANE 2
#define NUM_OF_OBJ 4*DISTANCE_LANE //Khoang cach giua dong xe 1 voi dong xe 2 (cung loai)
#define GREEN_TIME 7*1000/BASE_SPD //7s
#define RED_TIME 2*1000/BASE_SPD //2s

using namespace std;


class CCHARACTER {
protected:
	int mX, mY;
public:
	CCHARACTER(int x, int y) : mX(x), mY(y) {}
	//void draw(char, int); //old

	void Set(int x, int y);

	void get(int &x, int &y) const {
		x = mX;
		y = mY;
	}
	
	friend ostream& operator<<(ostream&, const CCHARACTER&);
	friend istream& operator >> (istream&, CCHARACTER&);
};


class CVEHICLE : public CCHARACTER {
protected:
	bool Left;
public:
	CVEHICLE() : CCHARACTER(0, 0) {}
	CVEHICLE(int x, int y) : CCHARACTER(x,y) {}
	virtual void Move() = 0;
	void setDir(bool l) {
		Left = l;
	}
	void setDir() {
		setDir(mY % 2);
	}
	bool isLeft() {
		return Left;
	}
	friend class CPEOPLE;
	virtual bool isHit(int x, int y) = 0;
	virtual void draw() = 0;
	virtual void clear() = 0;
};

class CTRUCK : public CVEHICLE {
	
public:
	CTRUCK(int x, int y) : CVEHICLE(x, y) {}
	CTRUCK() : CVEHICLE(0, 0) {}
	void Move();
	void draw();
	void clear();
	bool isHit(int x, int y);
};

class CCAR : public CVEHICLE {
public:
	CCAR(int x, int y) : CVEHICLE(x, y) {}
	CCAR() : CVEHICLE(0, 0) {}
	void Move();
	void draw();
	void clear();
	bool isHit(int x, int y);
};

/* {
		int d = 1;
		if (Left)
			d = -1;
		mX += d;
		if (mX > WIDTH - 3)
			mX = 3;
		if (mX < 3)
			mX = WIDTH - 3;
	}*/

class CANIMAL : public CCHARACTER {
protected:
	bool Left;
public:
	CANIMAL() : CCHARACTER(0,0) {}
	CANIMAL(int x, int y) : CCHARACTER(x,y) {}
	virtual void Cry() = 0;
	virtual void Move() = 0;
	bool isLeft() {
		return Left;
	}
	void setDir(bool l) {
		Left = l;
	}
	void setDir() {
		setDir(mY % 2);
	}
	friend class CPEOPLE;
	virtual bool isHit(int x, int y) = 0;
	virtual void draw() = 0;
	virtual void clear() = 0;
};

class CDINOSAUR : public CANIMAL {
public:
	CDINOSAUR(int x, int y) : CANIMAL(x, y) {}
	CDINOSAUR() : CANIMAL(0, 0) {}
	void Move();
	void Cry();
	void draw();
	void clear();
	bool isHit(int x, int y);
};

class CBIRD :public CANIMAL {
public:
	CBIRD(int x, int y) : CANIMAL(x, y) {}
	CBIRD() : CANIMAL(0, 0) {}
	void Move();
	void Cry();
	void draw();
	void clear();
	bool isHit(int x, int y);
};

class CPEOPLE : public CCHARACTER {
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
	void draw();
};

class CLIGHT {
private:
	int mX, mY;
	int RedTime, GreenTime;
	bool green;
public:
	CLIGHT();
	CLIGHT(int x, int y);
	void set(int x, int y);
	void countDown(); //Dem nguoc 
	void reset();
	void draw();
	bool isGreen();
};

class CGAME {
	CVEHICLE **axt;
	CVEHICLE **axh;
	CANIMAL **akl;
	CANIMAL **ac;
	CPEOPLE *an;
	CLIGHT *al;
	int mlevel;
public:
	bool IsRunning = true;
	CGAME(); //Khoi tao du lieu cac doi tuong
	void levelUp(bool isDraw = true);
	int level() { return mlevel; }
	void drawBoard(); //Ve khung
	void drawGame(); //Ve tro choi
	void drawFull();
	void drawLight();
	void clearScr();
	~CGAME(); //Thu hoi bo nho
	CPEOPLE* getPeople(); //Lay thong tin nguoi
	CVEHICLE** getVehicle(); //Lay danh sach xe
	CANIMAL** getAnimal(); //Lay danh sach thu
	void allocThings();
	void deallocThings();
	void setPosDir();
	void resetGame(); //Reset
	void exitGame(thread*); //Thoat thread
	void startGame(); //Start
	bool loadGame(istream&); //Load game
	bool saveGame(ostream&); //Save game
	void resetSave(ostream&); //Fix save
	bool legalSave(); //test file Save
	void pauseGame(HANDLE); //Pause thread
	void resumeGame(HANDLE); //Resume thread
	void updatePosPeople(char);//Dieu khien CPEOPLE de di chuyen
	void updatePosVehicle(); //cho xe di chuyen
	void updatePosAnimal(); //Cho dong vat di chuyen
};