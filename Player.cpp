#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	arr = new int *[SHIPS];    
	for (int i = 0; i < SHIPS; i++)   
		arr[i] = new int[SHIPS];    

	for (int i = 0; i < SHIPS; i++)
		for (int j = 0; j < SHIPS; j++)
		arr[i][j] = 0;

	ships = new AbstractShip*[SHIPS];
	for (int i = 6; i < SHIPS; i++)
		ships[i] = new AbstractShip(1);

	for (int i = 3; i < 6; i++)
		ships[i] = new AbstractShip(2);

	for (int i = 1; i < 3; i++)
		ships[i] = new AbstractShip(3);

		ships[0] = new AbstractShip(4);

		quantity = 10;

		statusPlayer = Battle;
}

AbstractShip& Player::getShip(int i)
{
	return *ships[i];
}

int& Player::getStatusPlayer()
{
	return statusPlayer;
}

void Player::setStatusPlayer(int statusPlayer)
{
	this->statusPlayer = statusPlayer;
}

int& Player::getArr(int i, int j)
{
	return arr[i][j];
}

void Player::setArr(int i, int j, int value)
{
	arr[i][j] = value;
}

void Player::setQuantity(int quantity)
{
	this->quantity = quantity;
}

int & Player::getQuantity()
{
	return quantity;
}

vector<int>& Player::getNextShot()
{
	return nextShot;
}

int & Player::getNextShot(int i)
{
	return nextShot[i];
}

Player::~Player()
{
	for (int i = 0; i < SHIPS; i++) 
		delete[] arr[i];
	delete[] arr;

	for (int i = 0; i < SHIPS; i++)
		delete[]ships;
	delete[] ships;
}
