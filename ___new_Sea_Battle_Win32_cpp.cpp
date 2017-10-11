#include "stdafx.h"

SeaBattle* game;
HINSTANCE hInst;


HWND hScreen;
HBITMAP hBScreen;

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
		game = new SeaBattle;

		DialogBox(hInst, MAKEINTRESOURCE(MY_SCREENSAVER), hWnd, DlgScreen);

		game->randomships(USER);
		game->randomships(PC);

		//EndDialog(hWndImage, NULL);


		game->begin(hWnd);
		//SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		//SendMessage(hWnd, WM_SYSCOMMAND, SW_SHOW, 0);

		return TRUE;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) >= IDC_BUTTON100 && LOWORD(wParam) <= IDC_BUTTON199)
		{
			if (game->getPlayer(USER).getQuantity()==0) 
				MessageBox(0, L"Компьютер победил", L"Результат игры:", MB_OK);
			else if (game->getPlayer(PC).getQuantity() == 0)
				MessageBox(0, L"Поздравляем! Вы победили!", L"Результат игры:", MB_OK);
//			else game->shotPlayer(hWnd, LOWORD(wParam));
			else game->Shot(hWnd, LOWORD(wParam),PC);
		}
		else
		{
			if (LOWORD(wParam) == ID_NEW_GAME)
			{
				//DestroyWindow(hWnd);
				//PostQuitMessage(0);
				//delete game;
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



		hScreen = GetDlgItem(hWnd, MY_SCREENSAVER);
		hBScreen = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_SEABATTLE));
		SendMessage(GetDlgItem(hWnd, MYSCREENINIMAGE), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBScreen);

		//SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
//		SendMessage(hWnd, WM_SYSCOMMAND, SW_SHOW, 0);
		return TRUE;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return TRUE;
	case WM_COMMAND:
		//if (LOWORD(wParam) >= IDC_BUTTON100 && LOWORD(wParam) <= IDC_BUTTON199)

		return TRUE;
	}
	return FALSE;
}

