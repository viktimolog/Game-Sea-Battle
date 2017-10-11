#include "stdafx.h"
#include "AbstractShip.h"


AbstractShip::AbstractShip(int i)
{
	size = i;
	squares = new int[size];
	statusShip = shipNew;
	damage = size;
}

AbstractShip::AbstractShip() {}

int& AbstractShip::getDamage()
{
	return damage;
}

void AbstractShip::setDamage(int damage)
{
	this->damage = damage;
}

int& AbstractShip::getStatus()
{
	return statusShip;
}

void AbstractShip::setStatus(int statusShip)
{
	this->statusShip = statusShip;
}

int& AbstractShip::getSize()
{
	return size;
}

void AbstractShip::setSize(int i)
{
	size = i;
}

int& AbstractShip::getSquare(int i)
{
	return squares[i];
}


void AbstractShip::setSquare(int i, int value)
{
	squares[i] = value;
}


AbstractShip::~AbstractShip()
{
	delete []squares;
}
