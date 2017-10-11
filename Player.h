#pragma once
#include "stdafx.h"

class Player
{
	AbstractShip** ships;
	int statusPlayer;
	int** arr;
	int quantity;
	vector<int> nextShot;

public:
	Player();
	~Player();
	AbstractShip& getShip(int);
	int& getStatusPlayer();
	void setStatusPlayer(int);
	int& getArr(int, int);
	void setArr(int, int, int);
	void setQuantity(int);
	int& getQuantity();

	vector<int>& getNextShot();
	int& getNextShot(int);
};

