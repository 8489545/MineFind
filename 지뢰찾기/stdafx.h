#pragma once
#include<iostream>
#include<Windows.h>

#include"Tile.h"
#include"Map.h"





using namespace std;

inline void gotoxy(int x, int y)
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}