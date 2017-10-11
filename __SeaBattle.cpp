#include "stdafx.h"
#include "SeaBattle.h"


void SeaBattle::MarkKoord(int player, int koord)
{
	this->getPlayer(player).setArr(koord, 1);
	this->getPlayer(player).setArr(koord - 1, 1);
	this->getPlayer(player).setArr(koord + 1, 1);
	this->getPlayer(player).setArr(koord - 9, 1);
	this->getPlayer(player).setArr(koord - 10, 1);
	this->getPlayer(player).setArr(koord - 11, 1);
	this->getPlayer(player).setArr(koord + 9, 1);
	this->getPlayer(player).setArr(koord + 10, 1);
	this->getPlayer(player).setArr(koord + 11, 1);
}

void SeaBattle::randomships(int player)
{
	TCHAR tmp[128],temp[128];
	int polog, koord;
	srand(time(NULL));
	//—тавим 4палубник
	koord = rand() % SHIPS*SHIPS;
	while(this->getPlayer(player).getArr(koord)) koord = rand() % SHIPS*SHIPS;
	//koord = 27;
	wsprintf(tmp, L"%d", koord);
	if (koord > (SHIPS*SHIPS - 31))
	{
		polog = 0;//горизонтальное вправо
		while((koord % 10 + 3)>9) koord--;

		wcscpy(tmp,L"");
		for (int i = 0; i < 4; i++)
		{
			this->getPlayer(player).getShip(0).setSquare(i, koord);
			// ажда€ координата помечает себ€ и все соседние 1

			this->MarkKoord(player, koord);

			wsprintf(temp, L"%d", koord);
			wcscat(tmp, temp);
			wcscat(tmp, L", ");
			koord++;
		}
	}
	else
	{
		wcscpy(tmp, L"");
		polog = 1;//вертикальное вниз
		for (int i = 0; i < 4; i++)
		{
			this->getPlayer(player).getShip(0).setSquare(i, koord);
			// ажда€ координата помечает себ€ и все соседние 1

			this->MarkKoord(player, koord);

			wsprintf(temp, L"%d", koord);
			wcscat(tmp, temp);
			wcscat(tmp, L", ");
			koord += 10;
		}

	}

	MessageBox(0,tmp, L" оординаты 4палубника",MB_OK);




}

Player& SeaBattle::getPlayer(int i)
{
	return players[i];
}

SeaBattle::SeaBattle()
{
	players = new Player[2];
}


SeaBattle::~SeaBattle()
{
	delete players;
}
