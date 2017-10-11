#include "stdafx.h"

SeaBattle* game;
HINSTANCE hInst;

HANDLE hThread1, hThread2;
DWORD dwThread1, dwThread2;

DWORD WINAPI Thread1(PVOID game)
{
	SeaBattle* sea = (SeaBattle*)game;
	sea->randomships(USER);
	return 0;
}

DWORD WINAPI Thread2(PVOID game)
{
	SeaBattle* sea = (SeaBattle*)game;
	sea->randomships(PC);
	return 0;
}

BOOL CALLBACK DlgCalc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgScreen(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR LpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(MY_DIALOG1), NULL, DlgCalc);
}

BOOL CALLBACK DlgCalc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:

		DialogBox(hInst, MAKEINTRESOURCE(MY_SCREENSAVER), 0, DlgScreen);

		game->begin(hWnd);

		return TRUE;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) >= IDC_BUTTON100 && LOWORD(wParam) <= IDC_BUTTON199)
		{
			if (game->getPlayer(USER).getQuantity() == 0)
				MessageBox(0, L"Компьютер победил", L"Результат игры:", MB_OK);
			else if (game->getPlayer(PC).getQuantity() == 0)
				MessageBox(0, L"Поздравляем! Вы победили!", L"Результат игры:", MB_OK);
			else game->Shot(hWnd, LOWORD(wParam), PC);//ход юзера
		}
		else
		{
			if (LOWORD(wParam) == ID_NEW_GAME)
			{
				ShowWindow(hWnd, SW_HIDE);
				game = new SeaBattle;
				game->randomships(USER);
				game->randomships(PC);
				ShowWindow(hWnd, SW_SHOW);
				game->begin(hWnd);
			}
			else if (LOWORD(wParam) == ID_EXIT)
			{
				DestroyWindow(hWnd);
				PostQuitMessage(0);
			}
			else if (LOWORD(wParam) == ABOUT)
			{
				MessageBox(0, L"Коганов А.В., 2016 год", L"Морской бой v1.0:", MB_OK);
			}

		}
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK DlgScreen(HWND hWndImage, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:

		game = new SeaBattle;
		SetTimer(hWndImage, 1, 1000, NULL);

		return TRUE;

	case WM_TIMER:

		KillTimer(hWndImage, 1);

		if (hThread1 && hThread2)
		{
			DWORD dwRes1;
			DWORD dwRes2;
			GetExitCodeThread(hThread1, &dwRes1);
			GetExitCodeThread(hThread1, &dwRes2);

			if (dwRes1 != STILL_ACTIVE && dwRes2 != STILL_ACTIVE)
			{
				KillTimer(hWndImage, 1);
				CloseHandle(hThread1);
				CloseHandle(hThread2);

				EndDialog(hWndImage, 0);
				return TRUE;
			}

			return TRUE;
		}
		else
		{
			hThread1 = CreateThread(NULL, 0, Thread1, game, CREATE_SUSPENDED, &dwThread1);
			hThread2 = CreateThread(NULL, 0, Thread2, game, CREATE_SUSPENDED, &dwThread2);

			ResumeThread(hThread1);
			Sleep(1000);
			ResumeThread(hThread2);

			SetTimer(hWndImage, 1, 1000, NULL);
		}

		return TRUE;

	case WM_CLOSE:
		DestroyWindow(hWndImage);
		PostQuitMessage(0);
		return TRUE;
	case WM_COMMAND:

		return TRUE;
	}
	return FALSE;
}
