// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//
#define SHIPS 10
#define USER 0
#define PC 1
#define ButtonBeginId 1012
#define ButtonEndId 1211
#define shipNew 0
#define shipPip 1
#define shipDead 2
#define Battle 2//������ Player ���� ������ �� �����
#define Hit 1	//������ Player ����� ����� �������
#define playerLose 0
#define playerWin 1
#define hit 1//���������
#define mark -2//�������� ��� ��� ��������
#define wasstep -1//����� ��� ��� ���


#pragma once
using namespace std;
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ��������� ����� ������������ ���������� �� ���������� Windows
// ����� ���������� Windows:
#include <windows.h>

// ����� ���������� C RunTime
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <wchar.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include<thread>
#include<vector>

#include "AbstractShip.h"
#include "Player.h"
#include "SeaBattle.h"
#include "resource.h"


// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������
