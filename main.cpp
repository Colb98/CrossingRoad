#include <thread>
#include <conio.h>
#include <vector>
#include <string>
#include <fstream>
#include "ConsoleControl.h"
#include "GameElements.h"

#define MID_POS 50

void SubThread();
int Menu();
int PauseMenu();
void writeOption(string s, int pos, bool isChosen);

char MOVING;
CGAME *cg;

int main() {
	cg = new CGAME();
	char temp;
	int choice;
	FixConsoleWindow();
	ShowConsoleCursor(false);
	choice = Menu();
	if (choice == 3) {
		delete cg;
		return 0;
	}
	if(choice == 0)
		cg->startGame();

	thread t1(SubThread);
	while (1) {
		temp = toupper(_getch());
		if (!cg->getPeople()->isDead()) {			
			if (temp == 27 || temp == 'P') {
				cg->pauseGame(t1.native_handle());
				choice = PauseMenu();
				cg->resumeGame((HANDLE)t1.native_handle());
				if (choice <= 3) {
					cg->drawFull();					
				}
				else {
					cg->exitGame(&t1);
					return 0;
				}
			}
			//else if (temp == 'P') {
			//	cg->pauseGame(t1.native_handle());
			//}
			else {
				cg->resumeGame((HANDLE)t1.native_handle());
				MOVING = temp;
			}
		}
		else {		
			//Sleep(300);
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
			cg->clearScr();
			GotoXY(WIDTH/2 - 36/2, HEIGHT / 2);
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
	cg->clearScr();
	for (int i = 0;i < numOChoice;i++)
		writeOption(selection[i], i + 1, chosen == i);

	while((key=toupper(_getch()))!=13 || (chosen == 2)) {
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
	
	//choose load file
	if (chosen == 1) {
		cg->clearScr();
		int chosen1 = 0;
		vector<string> load = { "Save slot 1", "Save slot 2","Save slot 3","Back"};
		int numOfChoice = load.size();
		for (int i = 0;i < numOfChoice;i++)
			writeOption(load[i], i + 1, chosen1 == i);

		while ((key = toupper(_getch())) != 13) {
			if (key == 'W') {
				chosen1 -= 1;
				if (chosen1 < 0)
					chosen1 = numOChoice - 1;
			}
			else if (key == 'S') {
				chosen1 += 1;
				if (chosen1 == numOChoice)
					chosen1 = 0;
			}
			else continue;
			for (int i = 0;i < numOChoice;i++)
				writeOption(load[i], i + 1, chosen1 == i);

		}
		if (chosen1 == 3) 
			return Menu(); // Quay lai menu (de quy cho tien)

		ifstream f;
		ofstream f1;
		bool flag = 0;
		switch (chosen1) {
		case 0: 
			f.open("save1.sav");
			if (f.is_open())
				flag = !(cg->loadGame(f));
			else
				flag = 1;
			break;
		case 1:
			f.open("save2.sav");
			if (f.is_open())
				flag = !(cg->loadGame(f));
			else
				flag = 1;
			break;
		case 2:
			f.open("save3.sav");
			if (f.is_open())
				flag = !(cg->loadGame(f));
			else
				flag = 1;
			break;
		}
		f.close();
		
		
		if (flag) {

			//select buggy save
			switch (chosen1) {
			case 0:
				f1.open("save1.sav");
				break;
			case 1:
				f1.open("save2.sav");
				break;
			case 2:
				f1.open("save3.sav");
				break;
			}

			setColor(13);
			writeOption("Something is wrong, starting new game", 5, false);
			for (int i = 0;i < 3;i++) {
				cout << '.';
				Sleep(500);
			}
			setColor(15);
			cg->resetSave(f1);
			f1.close();
			return 0;
		}
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


// Xoa man, In ra menu, save neu co, tra ve thu dc chon
int PauseMenu() {
	vector<string> selection = { "Resume Game","Save Game slot 1","Save Game slot 2","Save Game slot 3","Exit" };
	int chosen = 0;
	int numOfChoice = selection.size();
	char key;
	cg->clearScr();

	for(int i =0;i<numOfChoice;i++)
		writeOption(selection[i], i + 1, chosen == i);

	while (chosen != 0 || chosen != numOfChoice - 1) {
		while ((key = toupper(_getch())) != 13) {
			if (key == 'W') {
				chosen -= 1;
				if (chosen < 0)
					chosen = numOfChoice - 1;
			}
			else if (key == 'S') {
				chosen += 1;
				if (chosen == numOfChoice)
					chosen = 0;
			}
			else continue;
			for (int i = 0;i < numOfChoice;i++)
				writeOption(selection[i], i + 1, chosen == i);

		}

		bool flag = 0;
		ofstream f;

		switch (chosen) {
		case 1:
			f.open("save1.sav");
			if (f.is_open())
				flag = !(cg->saveGame(f));
			else
				flag = 1;
			f.close();
			break;

		case 2:
			f.open("save2.sav");
			if (f.is_open())
				flag = !(cg->saveGame(f));
			else
				flag = 1;
			f.close();
			break;

		case 3:
			f.open("save3.sav");
			if (f.is_open())
				flag = !(cg->saveGame(f));
			else
				flag = 1;
			f.close();
			break;
		default:
			cg->clearScr();
			return chosen;
		}

		if (chosen <= 3 && chosen >= 1) {
			setColor(13);
			if (flag)
				writeOption("Cannot save game atm.", numOfChoice + 1, false);
			else
				writeOption("Saved successfully.", numOfChoice + 1, false);
			setColor(15);
		}

	}

	cg->clearScr();
	return chosen;
}