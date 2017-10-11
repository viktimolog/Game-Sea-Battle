#pragma once
#include "stdafx.h"

class AbstractShip
{
	int size;
	int damage;
	int statusShip;
	int* squares;
public:
	AbstractShip();
	AbstractShip(int);
	int& getDamage();
	int& getStatus();
	int& getSize();
	int& getSquare(int);
	void setSize(int);
	void setStatus(int);
	void setDamage(int);
	void setSquare(int, int);
	~AbstractShip();
};

