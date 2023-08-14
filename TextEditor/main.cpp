#include<Windows.h>
#include<Richedit.h>
#include"resource.h"

CONST CHAR g_sz_CLASS_NAME[] = "Text Editor PV_211";
//g_ - Global
//sz_ - string zero, строка заканчивающаяся нулем


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//объявление процедуры окна

BOOL LoadTextFileToEdit(HWND hEdit, LPCSTR lpszFileName);
BOOL SaveTextFileFromEdit(HWND hEdit, LPCSTR lpszFileName);
//


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна
	WNDCLASSEX wc; //создаём структуру виндоу класс
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	//размеры
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	//внешний вид
	wc.hIcon = (HICON)LoadImage(hInstance, "fdd.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "fdd.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;  //имя функции это указатель на функцию
	wc.lpszClassName = g_sz_CLASS_NAME;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);//вбили данные, но функцию не зарегестрировали

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Info", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2)Создание окна
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_CLASS_NAME,	//Window Class name
		g_sz_CLASS_NAME,	//Window Title
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,	//Position
		CW_USEDEFAULT, CW_USEDEFAULT,	//Window size
		NULL,	//Parent
		NULL,   //(HMENU)IDR_MAIN_MENU// - this value doesn't work,
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//3)Запуск цикла сообщений
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static CHAR szFileName[MAX_PATH] = {};
	static CHAR szFileContent = NULL;
	switch (uMsg)
	{
	case WM_CREATE:
	{
		LoadLibrary("riched20.dll");
		RECT window_rect;
		RECT client_rect;
		GetWindowRect(hwnd, &window_rect);
		GetClientRect(hwnd, &client_rect);
		//MessageBox(hwnd, "Rects aquired", "Info", MB_OK);
		HWND hEdit = CreateWindowEx
		(
			NULL, RICHEDIT_CLASS, "",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, //| WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
			0, 0,	//start position
			client_rect.right, client_rect.bottom,
			hwnd,
			(HMENU)IDC_EDIT, //было NULL, в resourse.h создали #define IDC_EDIT 1000 это hEdit ресурс 
			GetModuleHandle(NULL),
			NULL
		);
	}

	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_FILE_OPEN: //загрузить файл
		{
			//CHAR szFileName[MAX_PATH]{};//создаём
			OPENFILENAME ofn;//объявляем структуру
			ZeroMemory(&ofn, sizeof(ofn));

			//инициализируем поля структуры
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			//фильтры
			ofn.lpstrFilter = "Text files: (*.txt)\0*.txt\0All files (*.*)\0*.*\0";
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;//максимально возможная длина пути
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;//OFN_EXPLORER-Чтобы отобразить диалоговое окно множественного
			//выбора в стиле проводника, OFN_FILEMUSTEXIST - файл должен существовать, OFN_HIDEREADONLY - скрыть только для чтения 
			ofn.lpstrDefExt = "txt";//расширение

			if (GetOpenFileName(&ofn)) LoadTextFileToEdit(GetDlgItem(hwnd, IDC_EDIT), szFileName);

		}
		break;
		case ID_FILE_SAVE:
		{
			if (szFileName[0] == 0)
				SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVEAS, 0);
			else
				SaveTextFileFromEdit(GetDlgItem(hwnd, IDC_EDIT), szFileName);
		}
		break;
		case ID_FILE_SAVEAS://сохранить как - пункт менюшки реализуем
		{
			//CHAR szFileName[MAX_PATH] = {}; //в этой строке будет храниться имя файла которое мы сохраняем

			OPENFILENAME ofn;//создали экземпляр структуры ofn
			ZeroMemory(&ofn, sizeof(ofn)); //зануляем её
			ofn.lStructSize = sizeof(ofn); //должны быть одного размера
			ofn.hwndOwner = hwnd;// родительское окно
			ofn.lpstrFilter = "Text files (*.txt)\0*.txt\0AllFiles (*.*)\0*.*\0";	//Double NULL-Terminated line, фильтры тип файла
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;//открывыть или сохранять файлы,внешний вид окна
			ofn.lpstrDefExt = "txt";//расширение по умолчанию
			//
			if (GetSaveFileName(&ofn))SaveTextFileFromEdit(GetDlgItem(hwnd, IDC_EDIT), szFileName);//вызываем нашу функцию
		}
		break;
		}
	}
	break;
	case WM_DESTROY:PostQuitMessage(0); break;
	case WM_CLOSE:
	{
		//CHAR sz_buffer[INT_MAX/2] = {};
		BOOL close = FALSE;
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		DWORD dwTextLength = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
		LPSTR lpszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
		if (lpszText != NULL)
		{
			SendMessage(hEdit, WM_GETTEXT, UINT_MAX, (LPARAM)lpszText);
			if (lpszText[0])
			{
				switch (MessageBox(hwnd, "сохранить изменения?", "Вопрос", MB_YESNOCANCEL | MB_ICONQUESTION))
				{
				case IDYES: SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVE, 0);
				case IDNO:  close = TRUE;
					//case IDCANCEL:return DefWindowProc(hwnd, uMsg, wParam, lParam); break;
				}
			}
			else close = TRUE;
				GlobalFree(lpszText);
		}		
			if (close)DestroyWindow(hwnd);
	}
	break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam); break;
	}
	return 0;
	//
}
//функция которая позволит открыть файл
BOOL LoadTextFileToEdit(HWND hEdit, LPCSTR lpszFileName)

{
	BOOL bSuccess = FALSE;
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_READ/*тип открытия файла*/, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE) //недействительное хранящее значение
	{
		DWORD dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != UINT_MAX)//если не равно макс размеру текстовый файл 4ГБ
		{
			LPSTR lpszFileText = (LPSTR)GlobalAlloc(GPTR, dwFileSize + 1);//выделили память
			if (lpszFileText) //если не равен нулю
			{
				DWORD dwRead;
				if (ReadFile(hFile, lpszFileText, dwFileSize, &dwRead, NULL))// в индикатор &dwRead записывается сколько мы прочитали из файлика
				{
					lpszFileText[dwFileSize] = 0;//зануляем 
					if (SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)lpszFileText))bSuccess = TRUE;//если вместо lpszFileText lpszFileName, то в текст
					//загоняется имя файла (весь путь)
				}
				GlobalFree(lpszFileText);
			}
			CloseHandle(hFile);
		}
	}
	return bSuccess;
}

BOOL SaveTextFileFromEdit(HWND hEdit, LPCSTR lpszFileName)
{
	BOOL bSuccess = FALSE;
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwTextLength = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);//получаем hEdit как параметр
		if (dwTextLength > 0)
		{
			LPSTR lpszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);//наподобии оператора new, GlobalAlloc выделяет память
			if (lpszText)//если указатель не пустой
			{
				if (SendMessage(hEdit, WM_GETTEXT, dwTextLength + 1, (LPARAM)lpszText))//dwTextLength - сколько текста,lpszText куда мы его ложим
				{//если вернули ненулевое значение
					DWORD dwWritten;
					if (WriteFile(hFile, lpszText, dwTextLength, &dwWritten, NULL))bSuccess = TRUE;
				}
				GlobalFree(lpszText);//если мы вызвали new вызываем delete - этим очищаем текстовый буфер
			}
		}
		CloseHandle(hFile); //закрыть деструктор
	}
	return bSuccess;

}