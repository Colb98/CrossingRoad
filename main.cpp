#include <thread>
#include <conio.h>
#include <vector>
#include <string>
#include "ConsoleControl.h"
#include "GameElements.h"

#define MID_POS 50

void SubThread();
int Menu();
void writeOption(string s, int pos, bool isChosen);

char MOVING;
CGAME *cg;

int main() {
	cg = new CGAME();
	int temp;
	int choice;
	FixConsoleWindow();
	ShowConsoleCursor(false);
	choice = Menu();
	if (choice == 3) {
		delete cg;
		return 0;
	}
	cg->startGame();
	thread t1(SubThread);
	while (1) {
		temp = toupper(_getch());
		if (!cg->getPeople()->isDead()) {
			if (temp == 27) {
				cg->exitGame(&t1);
				return 0;
			}
			else if (temp == 'P') {
				cg->pauseGame(t1.native_handle());
			}
			else {
				cg->resumeGame((HANDLE)t1.native_handle());
				MOVING = temp;
			}
		}
		else {
			if (temp == 'Y') {
				cg->startGame();
			}
			else {
				cg->exitGame(&t1);
				return 0;
			}
		}
	}
	cg->drawBoard();
	GotoXY(0, 22);
	delete[] cg;
	return 0;
}

void SubThread() {
	while (cg->IsRunning) {
		while (cg->getPeople()->isDead()) {
			if (!cg->IsRunning)
				return;
			Sleep(500);
		}
		if (!cg->getPeople()->isDead()) {
			cg->updatePosPeople(MOVING);
		}
		MOVING = ' ';
		cg->updatePosVehicle();
		cg->updatePosAnimal();
		cg->drawGame();
		if (cg->getPeople()->isImpact(cg->getVehicle(),cg->level()) || cg->getPeople()->isImpact(cg->getAnimal(),cg->level()))
		{			
			//Xu li khi va cham (thoat ra, hien chu blah blah)
			GotoXY(0, HEIGHT + 5);
			cout << "You are lose, press Y to play again";
		}
		if (cg->getPeople()->isFinish()) {
			//Ve dich, tang level
			cg->clearScr();
			if (cg->level() < MAX_LEVEL)
				cg->levelUp();
			else 
				cg->startGame();
					
			Sleep(500);
		}
		Sleep(BASE_SPD);
	}
}

int Menu() {
	vector<string> selection = { "Start Game","Load Game","Settings","Exit" };
	int chosen = 0;
	int numOChoice = selection.size();
	char key = ' '; // init 

	for (int i = 0;i < numOChoice;i++)
		writeOption(selection[i], i + 1, chosen == i);

	while((key=toupper(_getch()))!=13 || (chosen!=0 && chosen!=numOChoice-1)) {
		if (key == 'W') {
			chosen -= 1;
			if (chosen < 0)
				chosen = numOChoice - 1;
		}
		else if (key == 'S') {
			chosen += 1;
			if (chosen == numOChoice)
				chosen = 0;
		}
		else continue;
		for (int i = 0;i < numOChoice;i++)
			writeOption(selection[i], i + 1, chosen == i);
		
	} 
	return chosen;
}

void writeOption(string s, int pos, bool isChosen) {
	if (isChosen)
		setColor(176);
	int len = s.length();
	GotoXY(MID_POS - (len - len / 2), 8 + pos*2);
	cout << s;
	if (isChosen)
		setColor(15);
}
