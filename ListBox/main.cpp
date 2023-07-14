#include<Windows.h>
#include"resource.h"

CONST CHAR* values[] = { "This","is","my","second","Combo","Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR IpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);//
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		break;
		HWND hSTR = GetDlgItem(hwnd, IDC_LIST_STR);
		for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++)
		{
			SendMessage(hSTR, WM_GETTEXT, 0, (LPARAM)values[i]);
		}
	}
	case WM_COMMAND:
	{
	//case IDOK: 
	// 
		//break;
	case IDCANCEL: EndDialog(hwnd, 0); 
	}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);

	}
	return FALSE;
}