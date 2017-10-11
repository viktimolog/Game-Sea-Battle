#include "stdafx.h"

int SeaBattle::shotPChit()
{
	int shot = 0, size = 0;

	if (getPlayer(USER).getStatusPlayer() == Battle || !getPlayer(USER).getNextShot().size())   //�� ����� ���� ����,������� USER
	{
		return shot = rand() % (SHIPS*SHIPS);
	}
	else
	{
		size = getPlayer(USER).getNextShot().size();
		shot = getPlayer(USER).getNextShot(size-1);
		getPlayer(USER).getNextShot().pop_back();
	}
	return shot;
}

int SeaBattle::Shot(HWND hWnd, int id, int player)
{
	TCHAR deadship[32], pipship[32], miss[32], victory[32];
	HBITMAP hBitmap;
	int a = 0, b = 0, shot, key = -1;
	if (player == PC)	//�� ����� ���� ����, �� ���� ��� ��������
	{
		shot = id - ButtonBeginId - SHIPS*SHIPS;
		wcscpy(deadship, L"�� �������� �������!");
		wcscpy(pipship, L"�� ������ �������!");
		wcscpy(miss, L"����� ����, �� �� ������������!");
		wcscpy(victory, L"�����������! �� ��������!");
		a = shot / 10;
		b = shot % 10;
		if (this->getPlayer(player).getArr(a, b) == wasstep)//����� ��� ���
		{
			//!!!	MessageBox(0, L"���� �� ��� ������!", L"��������� ��������:", MB_OK | MB_ICONWARNING);
			return 0;
		}
	}

	else      //��� �����
	{
		shot = shotPChit();
		id = shot + ButtonBeginId;
		wcscpy(deadship, L"��������� ������� ��� �������!");
		wcscpy(pipship, L"��������� ����� ��� �������!");
		wcscpy(miss, L"���! ��������� �����������!");
		wcscpy(victory, L"����� ����, �� �� ���������!");

			a = shot / 10;
			b = shot % 10;

		if (this->getPlayer(player).getArr(a, b) == wasstep || this->getPlayer(player).getArr(a, b) == mark)
		{
			//���� ���� ������ �������� � ������, ���� ��� ��� ��� ���� ��� ����� ��� ��������(-2), �� ��� ��� �� �����
			this->Shot(hWnd, id, USER);
			return 0;
		}
	}

	this->getPlayer(player).setArr(a, b, wasstep); //��������, ��� �������� � ��� ����������, wasstep = -1

	for (int i = 0; i < SHIPS; i++)
	{
		if (key != -1) break;
		int square, size = this->getPlayer(player).getShip(i).getSize();
		for (int j = 0; j < size; j++)
		{
			square = this->getPlayer(player).getShip(i).getSquare(j);
			if (square == shot)
			{
				key = i;
				break;
			}
		}
	}
	if (key != -1)//���������
	{
		if (getPlayer(player).getShip(key).getSize() == 1)//����� � ������������
		{
			getPlayer(player).setStatusPlayer(Battle);
			for (int i = a - 1; i <= a + 1; i++)
				if (i >= 0 && i < SHIPS && (b - 1) >= 0 && (b - 1) < SHIPS)
					this->getPlayer(player).setArr(i, b - 1, mark);

			for (int i = a - 1; i <= a + 1; i++)
				if (i >= 0 && i < SHIPS && (b + 1) >= 0 && (b + 1) < SHIPS)
					this->getPlayer(player).setArr(i, b + 1, mark);

			for (int i = a - 1; i <= a + 1; i += 2)
				if (i >= 0 && i < SHIPS && b >= 0 && b < SHIPS)
					this->getPlayer(player).setArr(i, b, mark);

			this->getPlayer(player).getShip(key).setStatus(shipDead);
			this->getPlayer(player).getShip(key).setSize(0);//������� ���� ��� ������ ������ 0 ����� ������ �� ���������� ��� ��������
			this->getPlayer(player).setQuantity(--this->getPlayer(player).getQuantity());
			hBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_CROSS));
			SendMessage(GetDlgItem(hWnd, id), BM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)hBitmap);
			MessageBox(0, deadship, L"��������� ��������:", MB_OK | MB_ICONWARNING);
		}
		else //��������� �� � ������������
		{
			getPlayer(player).setStatusPlayer(Hit);
			getPlayer(player).getShip(key).setDamage(--this->getPlayer(player).getShip(key).getDamage());
			hBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_CROSS));
			SendMessage(GetDlgItem(hWnd, id), BM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)hBitmap);
			if (!this->getPlayer(player).getShip(key).getDamage())
				//���������� ��������� ����� ���������� ����� �������, �� ���� �������, ����� ����
			{
				if(getPlayer(player).getNextShot().size()) getPlayer(player).getNextShot().clear();
				getPlayer(player).setStatusPlayer(Battle);
				getPlayer(player).getShip(key).setSize(0);//������� ���� ��� ������ ������ 0 ����� ������ �� ���������� ��� ��������
				getPlayer(player).setQuantity(--this->getPlayer(player).getQuantity());
				getPlayer(player).getShip(key).setStatus(shipDead);
				MessageBox(0, deadship, L"��������� ��������:", MB_OK | MB_ICONWARNING);
			}
			else //���������� ��������� ������ ������� �������
			{			
				if(getPlayer(player).getShip(key).getStatus() == shipNew)
				{
					if (getPlayer(player).getNextShot().size())
							getPlayer(player).getNextShot().clear();

					if (getPlayer(player).getShip(0).getStatus() != shipDead)	//4�������� ���
					{
					//	MessageBox(0, L"", L"4�������� ���:", MB_OK | MB_ICONWARNING);

						if ((b - 3) >= 0)  getPlayer(player).getNextShot().push_back(a * 10 + b - 3);
						if ((b - 2) >= 0)  getPlayer(player).getNextShot().push_back(a * 10 + b - 2);
						if ((b - 1) >= 0)  getPlayer(player).getNextShot().push_back(a * 10 + b - 1);

						if ((b + 3) < SHIPS)  getPlayer(player).getNextShot().push_back(a * 10 + b + 3);
						if ((b + 2) < SHIPS)  getPlayer(player).getNextShot().push_back(a * 10 + b + 2);
						if ((b + 1) < SHIPS)  getPlayer(player).getNextShot().push_back(a * 10 + b + 1);

						if ((a - 3) >= 0)  getPlayer(player).getNextShot().push_back((a - 3) * 10 + b);
						if ((a - 2) >= 0)  getPlayer(player).getNextShot().push_back((a - 2) * 10 + b);
						if ((a - 1) >= 0)  getPlayer(player).getNextShot().push_back((a - 1) * 10 + b);

						if ((a + 3) < SHIPS)  getPlayer(player).getNextShot().push_back((a + 3) * 10 + b);
						if ((a + 2) < SHIPS)  getPlayer(player).getNextShot().push_back((a + 2) * 10 + b);
						if ((a + 1) < SHIPS)  getPlayer(player).getNextShot().push_back((a + 1) * 10 + b);
					}

					else if (getPlayer(player).getShip(1).getStatus() != shipDead || getPlayer(player).getShip(2).getStatus() != shipDead)
						//��� ���� ���� ������������
					{
						if ((b - 2) >= 0)  getPlayer(player).getNextShot().push_back(a * 10 + b - 2);
						if ((b - 1) >= 0)  getPlayer(player).getNextShot().push_back(a * 10 + b - 1);

						if ((b + 2) < SHIPS)  getPlayer(player).getNextShot().push_back(a * 10 + b + 2);
						if ((b + 1) < SHIPS)  getPlayer(player).getNextShot().push_back(a * 10 + b + 1);

						if ((a - 2) >= 0)  getPlayer(player).getNextShot().push_back((a - 2) * 10 + b);
						if ((a - 1) >= 0)  getPlayer(player).getNextShot().push_back((a - 1) * 10 + b);

						if ((a + 2) < SHIPS)  getPlayer(player).getNextShot().push_back((a + 2) * 10 + b);
						if ((a + 1) < SHIPS)  getPlayer(player).getNextShot().push_back((a + 1) * 10 + b);
					}

					else if (getPlayer(player).getShip(3).getStatus() != shipDead || getPlayer(player).getShip(4).getStatus() != shipDead
						|| getPlayer(player).getShip(5).getStatus() != shipDead)
						//��� ���� ���� ������������
					{
						if ((b - 1) >= 0)  getPlayer(player).getNextShot().push_back(a * 10 + b - 1);

						if ((b + 1) < SHIPS)  getPlayer(player).getNextShot().push_back(a * 10 + b + 1);

						if ((a - 1) >= 0)  getPlayer(player).getNextShot().push_back((a - 1) * 10 + b);

						if ((a + 1) < SHIPS)  getPlayer(player).getNextShot().push_back((a + 1) * 10 + b);
					}					
				}
				getPlayer(player).getShip(key).setStatus(shipPip);

				getPlayer(player).setStatusPlayer(Hit);//shot ���� �������� �����



				///!!!	MessageBox(0, pipship, L"��������� ��������:", MB_OK | MB_ICONWARNING);
			}
		}
	}
	else	//�� �����
	{
		hBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_SEA));
		SendMessage(GetDlgItem(hWnd, id), BM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)hBitmap);
		//!!!MessageBox(0, miss, L"��������� ��������:", MB_OK | MB_ICONINFORMATION);
	}

	if (this->getPlayer(player).getQuantity() == 0)
		MessageBox(0, victory, L"��������� ����:", MB_OK | MB_ICONINFORMATION);

	else if (player == PC) this->Shot(hWnd, id, USER);	//��������� ��� �����, ���� ����� �����, ��������� ���� ������ USER

	return 0;
}

void SeaBattle::begin(HWND hWnd)
{
	HBITMAP hBitmap;

	for (int i = 0; i < SHIPS*SHIPS * 2; i++)
	{
		hBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_CLEAR));
		SendMessage(GetDlgItem(hWnd, IDC_BUTTON0 + i), BM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)hBitmap);
	}

	for (int i = 0; i < SHIPS; i++)
	{
		int square, size = this->getPlayer(USER).getShip(i).getSize();
		for (int j = 0; j < size; j++)
		{
			square = this->getPlayer(USER).getShip(i).getSquare(j);
			hBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_ZERO));
			SendMessage(GetDlgItem(hWnd, IDC_BUTTON0 + square), BM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)hBitmap);
		}
	}
}

int SeaBattle::magicKoord(int i, int j)
{
	int res;
	if (i != 0) res = i * 10 + j;
	else res = j;

	return res;
}

int SeaBattle::correctKoord(int player, int i, int j)
{
	if (i > SHIPS - 1 || i<0 || j>SHIPS - 1 || j < 0) return 0;

	else if (this->getPlayer(player).getArr(i, j) != 0) return 0;

	else
	{
		for (int b = j - 1; b <= j + 1; b++)
			for (int a = i - 1; a <= i + 1; a++)
				if (a >= 0 && b >= 0 && a < SHIPS && b < SHIPS)
					if (this->getPlayer(player).getArr(a, b) != 0)
						return 0;
	}
	return 1;
}


void SeaBattle::MarkKoord(int player, int i, int j)
{
	this->getPlayer(player).setArr(i, j, 1);	//����� 1 ������ �������

	for (int b = j - 1; b <= j + 1; b++)
		for (int a = i - 1; a <= i + 1; a++)
			if (a >= 0 && b >= 0 && a < SHIPS && b < SHIPS)
				this->getPlayer(player).setArr(a, b, 1);  //����� 1 ��� ��������
}

void SeaBattle::randomships(int player)
{
	TCHAR ttt[128], tmp[128], temp[128];
	int v = 0, i, j, tmp_i, tmp_j, direction, key, size_ship, change_direction;

	int ship = 0;//� ����� ����� ���������� 10 ��������

	srand(time(NULL));

	while (ship < SHIPS)
	{
		if (ship > 5)size_ship = 1;     //� ����������� �� ���� ������� �������� ��� ����������
		else if (ship > 2)size_ship = 2;//���������� ������ ������������ �������. �������� � 4������
		else if (ship > 0)size_ship = 3;
		else size_ship = 4;

		wsprintf(tmp, L"");

		tmp_i = rand() % SHIPS;//�������� �������� ����������
		tmp_j = rand() % SHIPS;
		v++;

		direction = rand() % 2;//�������� �������� "��������������" ��������� (���/���)
		change_direction = 2;
		while (change_direction)//���� ��� �������� ����� ���������
		{
			if (direction)
			{
				if (tmp_i + size_ship < SHIPS)
				{//��������� ������ �� ����� ��� ������������� ����������
					key = 0;//��������� �������� "�������" ���� ��� ���������� �������

					for (i = tmp_i - 1; i <= tmp_i + size_ship; i++)//��������� ���� ��� ������� � ����������
						for (j = tmp_j - 1; j <= tmp_j + 1; j++)
							if (i < SHIPS&&i >= 0 && j < SHIPS&&j >= 0)
								if (this->getPlayer(player).getArr(i, j)) key++;//���� �� ��������� � �������� ����
													 //��������� ��� �� ������� �� ��� �����
													 //���� ������� ���� - ����������� �������.

					if (!key)
					{//��������� ���������� ������� ������ ���� ������� ������� 0
						for (i = 0; i < size_ship; i++)
						{
							this->getPlayer(player).setArr(tmp_i + i, tmp_j, 1);
							this->getPlayer(player).getShip(ship).setSquare(i, this->magicKoord(tmp_i + i, tmp_j));
							wsprintf(temp, L"%d", this->magicKoord(tmp_i + i, tmp_j));
							wcscat(tmp, temp);
							wcscat(tmp, L", ");
						}
						wsprintf(ttt, L"%d", size_ship);
						wcscat(ttt, L" ���������");
						ship++;//����������
					//	MessageBox(0, tmp, ttt, MB_OK);
						break;//���������� ����
					}
				}
				direction--;//���� �� ����������, �������� �����������
				change_direction--;//�������, ��� ���� ����������� ��� ���������
			}//��������� �������� ������������� ���������
			else {
				if (tmp_j + size_ship < SHIPS)
				{//��������� ������ �� ����� ��� ��������������� ����������
					key = 0;

					for (i = tmp_i - 1; i <= tmp_i + 1; i++)
						for (j = tmp_j - 1; j <= tmp_j + size_ship; j++)
							if (i < SHIPS&&i >= 0 && j < SHIPS&&j >= 0)
								if (this->getPlayer(player).getArr(i, j)) key++;

					if (!key)
					{

						for (i = 0; i < size_ship; i++)
						{
							this->getPlayer(player).setArr(tmp_i, tmp_j + i, 1);
							this->getPlayer(player).getShip(ship).setSquare(i, this->magicKoord(tmp_i, tmp_j + i));
							wsprintf(temp, L"%d", this->magicKoord(tmp_i, tmp_j + i));
							wcscat(tmp, temp);
							wcscat(tmp, L", ");
						}
						wsprintf(ttt, L"%d", size_ship);
						wcscat(ttt, L" ���������");
						ship++;
						//		MessageBox(0, tmp, ttt, MB_OK);
						break;//���������� ���������� ����
					}
				}
				direction++;//���� �� ����������, �������� �����������
				change_direction--;//�������, ��� ���� ����������� ��� ���������
			}//��������� �������� ��������������� ���������
		}//��������� while ���� ��� �������� ����� ���������
	}//��������� while ���� ���������� 10 ��������
	wsprintf(ttt, L"%d", v);
	wcscat(ttt, L" VAVA");
	//MessageBox(0, L"����� ������", ttt, MB_OK);
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
	delete[]players;
}
