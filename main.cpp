#include <thread>
#include <conio.h>
#include <vector>
#include <string>
#include <fstream>
#include "ConsoleControl.h"
#include "GameElements.h"

#define MID_POS 50
#define CHEAT_CODE "BUULOCDEPTRAI"

void SubThread();
int Menu();
int PauseMenu();
void writeOption(string s, int pos, bool isChosen);
void writeOption(string s, int pos, int color);

char MOVING;
CGAME *cg;
//Cheat mode sign
bool cheat_mode = false;
//To know when cheat mode is change
bool cheat_toggle = false;

//Testing main
//int main() {
//	CCAR a(5, 5);
//	CBIRD b(7, 8);
//	a.setDir(false);
//	while (!_kbhit()) {
//		a.Move();
//		a.draw();
//		b.Move();
//		b.draw();
//		
//		GotoXY(7, 5);
//		cout << 'Y';
//		GotoXY(0, 0);
//		cout << a.isHit(7, 5);
//
//		cout << endl << b.isHit(7, 5);
//		Sleep(100);
//	}
//	return 0;
//}

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
	if (choice == 0)
		cg->startGame();
	else if (choice == 1) {
		cg->drawBoard();
		cg->drawFull();
	}

	thread t1(SubThread);
	while (1) {
		temp = toupper(_getch());
		/*if (temp != 27 && temp != 'P' && temp != 'A' && temp != 'S' && temp != 'D' && temp != 'W')
			continue;*/
		if (!cg->getPeople()->isDead()) {			
			if (temp == CHEAT_CODE[0]) {
				int i = 1, n = strlen(CHEAT_CODE);
				while (i < n && (temp = toupper(_getch())) == CHEAT_CODE[i])
					i++;
				if (i == n) {
					cheat_mode = !cheat_mode;
					cheat_toggle = true;
				}
				
			}
			else if (temp == 27 || temp == 'P') {
				cg->pauseGame(t1.native_handle());
				choice = PauseMenu();
				cg->resumeGame((HANDLE)t1.native_handle());
				if (choice <= 2) {
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

		if (cheat_toggle) {
			GotoXY(0, HEIGHT + 3);
			cout << "                                ";
			GotoXY(0, HEIGHT + 3);
			if (cheat_mode)
				cout << "You unlocked cheat mode!!";
			else
				cout << "You turned off cheat mode";
			cheat_toggle = false;
		}

		MOVING = ' ';
		cg->updatePosVehicle();
		cg->updatePosAnimal();
		cg->drawGame();
		if(!cheat_mode)
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
			else {
				GotoXY(WIDTH / 2 - 36 / 2, HEIGHT / 2);
				cout << "Congratulation!!! You passed all 5 levels. Game will restart in 3 sec";
				Sleep(3000);
				cg->startGame();
			}
					
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

	writeOption("Start a new game at once", numOChoice + 1, 13);

	do {
		while ((key = toupper(_getch())) != 13) {
			writeOption("                              ", numOChoice + 1, 13);
			
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
			
			switch (chosen) {
			case 0: writeOption("Start a new game at once", numOChoice + 1, 13); break;
			case 1: writeOption("Load a saved game", numOChoice + 1, 13); break;
			case 2: writeOption("Ooops... Nothing's here", numOChoice + 1, 13); break;
			case 3: writeOption("Quit the game", numOChoice + 1, 13); break;
			}
		}
	} while (chosen == 2);
	
	//choose load file
	if (chosen == 1) {
		writeOption("Enter file name: ", numOChoice+1, 13);
		ifstream f;
		ofstream f1;
		string name;
		getline(cin, name);

		bool flag = 0;
		f.open(name);
		if (f.is_open())
			flag = !(cg->loadGame(f));
		else
			flag = 1;
		
		f.close();
		
		
		if (flag) {

			//select buggy save
			f1.open(name);

			setColor(13);
			writeOption("Something is wrong, starting new game", numOChoice+1, false);
			for (int i = 0;i < 3;i++) {
				cout << '.';
				Sleep(500);
			}
			setColor(BW);
			cg->resetSave(f1);
			f1.close();
			return 0;
		}
	}
	return chosen;
}

void writeOption(string s, int pos, int color) {
	setColor(color);
	int len = s.length();
	GotoXY(MID_POS - (len - len / 2), 8 + pos * 2);
	cout << s;
	setColor(BW);
}

void writeOption(string s, int pos, bool isChosen) {
	if (isChosen)
		setColor(176);
	int len = s.length();
	GotoXY(MID_POS - (len - len / 2), 8 + pos*2);
	cout << s;
	if (isChosen)
		setColor(BW);
}


// Xoa man, In ra menu, save neu co, tra ve thu dc chon
int PauseMenu() {
	vector<string> selection = { "Resume Game","Save Game","Load Game","Exit" };
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
		ifstream f1;
		string name;
		switch (chosen) {
		case 1:
			writeOption("Enter save file path: ", numOfChoice + 1, 13);
			getline(cin, name);
			f.open(name);
			if (f.is_open())
				flag = !(cg->saveGame(f));
			else
				flag = 1;
			f.close();
			break;
		case 2:
			writeOption("Enter save file path: ", numOfChoice + 1, 13);
			getline(cin, name);
			f1.open(name);
			if (f1.is_open())
				flag = !(cg->loadGame(f1));
			else
				flag = 1;
			f1.close();
			break;
		default:
			cg->clearScr();
			return chosen;
		}

		if (chosen == 1) {
			writeOption("                                         ", numOfChoice + 1, BW);
			if (flag)
				writeOption("Cannot save game right now.", numOfChoice + 1, 13);
			else
				writeOption("Saved successfully.", numOfChoice + 1, 13);
			
		}
		else {
			writeOption("                                         ", numOfChoice + 1, BW);
			if (flag)
				writeOption("Cannot open save file.", numOfChoice + 1, 13);
			else
				writeOption("Loaded successfully.", numOfChoice + 1, 13);			
		}

	}

	cg->clearScr();
	return chosen;
}