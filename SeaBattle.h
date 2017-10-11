#pragma once
#include "stdafx.h"

class SeaBattle
{
	Player* players;
public:
	int shotPChit();
	int Shot(HWND, int, int);
	void begin(HWND);
	int magicKoord(int, int);
	int correctKoord(int, int, int);
	void MarkKoord(int, int, int);
	void randomships(int);
	Player& getPlayer(int);
	SeaBattle();
	~SeaBattle();
};

