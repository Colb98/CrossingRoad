#pragma once

#include <Windows.h>
#define RED_BG 192
#define GREEN_BG 160
#define BW 15

void FixConsoleWindow();
void GotoXY(int, int);
void ShowConsoleCursor(bool);
void ClearScreen();


// Change text color

void setColor(int color);