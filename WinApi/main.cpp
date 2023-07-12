#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_LOGIN_INVITE[] = "Введите имя пользователя";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//MessageBox(NULL, "Привет мир! Я окно сообщения:-) ", "Info", MB_YESNOCANCEL | MB_ICONINFORMATION);
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);

	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: //создаём элементы окна
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITE);
	}	break;
	case WM_COMMAND:   //обрабатываем команды нажатия на кнопки, наведение мыши...
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:  // ID окна к которому обращаемся
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				if (strcmp(sz_buffer, g_sz_LOGIN_INVITE) == 0)
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
			}
			if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				if (strlen(sz_buffer) == 0)
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITE);
			}
		}
		break;
		case IDC_BUTTON_COPY:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);//получение хендлера окна
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			const int SIZE = 256;
			char sz_buffer[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(GetDlgItem(hwnd, IDC_STATIC_LOGIN), WM_SETTEXT, 0, (LPARAM)sz_buffer);

		}
		break;
		case IDOK: MessageBox(hwnd, "была нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}
