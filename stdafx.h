// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//
#define SHIPS 10
#define USER 0
#define PC 1
#define ButtonBeginId 1012
#define ButtonEndId 1211
#define shipNew 0
#define shipPip 1
#define shipDead 2
#define Battle 2//статус Player пока никого не ранил
#define Hit 1	//статус Player когда ранил корабль
#define playerLose 0
#define playerWin 1
#define hit 1//попадание
#define mark -2//заведомо там нет кораблей
#define wasstep -1//такой ход уже был


#pragma once
using namespace std;
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // »сключите редко используемые компоненты из заголовков Windows
// ‘айлы заголовков Windows:
#include <windows.h>

// ‘айлы заголовков C RunTime
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


// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
