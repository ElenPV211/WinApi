#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR g_sz_MY_WINDOW_CLASS[] = "MyFirstWindow";
//g-global, i-int
CONST INT g_i_BTN_SIZE = 50;// размер кнопки
CONST INT g_i_DISTANCE = 10; //расстояние между кнопками
CONST INT g_i_START_X = 10;  //отступ от начала окна по X
CONST INT g_i_START_Y = 10;  //отступ от начала окна по Y
CONST INT g_i_DISPLAY_WIDTH = (g_i_BTN_SIZE * 5 + g_i_DISTANCE * 4);
CONST INT g_i_DISPLAY_HEIGHT = 18;

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//процедура окна

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR IpCmdLine, INT nCmdShow)
{
	//1.Регистрация класса окна
	WNDCLASSEX wc; //объявляем класс структуры WNDCLASSEX с именем wc
	//зануляем экземпляр класса окна wc функцией
	ZeroMemory(&wc, sizeof(wc));

	//инициализируем экземпляр класса
	//поля связанные с размерами
	wc.cbSize = sizeof(wc); //размер класса в Байтах cb-Count Bytes
	wc.cbClsExtra = 0; //Class ExtraBytes дополнительные байты класса
	wc.cbWndExtra = 0; //WindowExtraBytes дополнительные байты окна
	wc.style = 0;

	//внешний вид окна, иконки и курсоры, их мы можем загрузить
   // wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_TREE));//отображается в панели задач
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_jupiter));//отображается в заголовке окна

	wc.hIcon = (HICON)LoadImage(hInstance, "tree.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "jupiter.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);

	wc.hCursor = (HCURSOR)LoadImage(hInstance, "Normal.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wc.hInstance = hInstance;
	wc.lpfnWndProc = (WNDPROC)WndProc; //процедура окна
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_MY_WINDOW_CLASS;//строка без которой выходит ошибка класс не зарегестрирован
	//lpsz(long pointer saiz zero) - указатель на строку


	//функция для регистрации структуры RegisterClassEx. проверка зарегестрирован ли класс
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Класс не зарегестрирован", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	//2 Создание окна
	 //вызываем функцию CreateWindowEx

	/*INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);

	INT window_width = screen_width * 3 / 4;
	INT window_height = screen_height * 3 / 4;

	INT start_x = screen_width / 8;
	INT start_y = screen_height / 8;*/

	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);

	INT window_width = g_i_START_X * 2 + g_i_DISPLAY_WIDTH + 16;
	INT window_height = g_i_START_Y * 2 + g_i_DISPLAY_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE) * 4 + 38;

	INT start_x = screen_width / 8;
	INT start_y = screen_height / 8;

	HWND hwnd = CreateWindowEx
	(
		0,
		g_sz_MY_WINDOW_CLASS,//имя класса окна 
		g_sz_MY_WINDOW_CLASS,//заголовок окна
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		//WS_OVERLAPPEDWINDOW,//за стиль окна отвечает класс окна и для каждого класса есть свой набор стилей
		//вы создаёте окно или кнопку или дрек даун, стиль окна определяется его классом
//Стиль окна для главного окна программы всегда будет WS_OVERLAPPEDWINDOW
		//WS_OVERLAPPEDWINDOW - это окно верхнего уровня (TOP_LEVEL_WINDOW), которое включает в себя дочерние окна (CHILDWINDOW)

		start_x, start_y, //начальная позиция окна (х,у положение на экране)
		window_width, window_height, //размер окна (ширина, высота)
		NULL,//Родительское окно, Parametr Window
		NULL,//для главного окна это меню, для дочернего окна это ID его ресурса
		hInstance,
		NULL
	);
	if (hwnd == 0)
	{
		MessageBox(NULL, "окно не было создано", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);//задаёт режим отображения окна
	UpdateWindow(hwnd);//выполняет прорисовку окна

	//3. Запуск цикла сообщенией

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);//транслирует сообщение виртуальных клавиш в символьное сообщение
		DispatchMessage(&msg); //отправляет сообщение в процедуру окна сообщение берёт от GetMessage
		//которое вынимает сообщение из очереди msg
	}
	return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE: //посылается в окно один раз
	{
		HWND hEdit = CreateWindowEx
		(
			NULL, //exStyle
			"Edit",
			"0",
			WS_CHILD | WS_VISIBLE | ES_RIGHT | WS_BORDER,
			g_i_START_X, g_i_START_Y,
			g_i_DISPLAY_WIDTH, g_i_DISPLAY_HEIGHT,
			hwnd, (HMENU)IDC_EDIT, GetModuleHandle(NULL), NULL
		);
		CHAR sz_btn_name[] = "0";
		INT number = 1;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_btn_name[0] = number + 48;
				CreateWindowEx
				(
					NULL,
					"Button",
					sz_btn_name,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					g_i_START_X + /*g_i_DISTANCE+*/  (g_i_BTN_SIZE + g_i_DISTANCE) * j,
					g_i_START_Y + g_i_DISTANCE + (g_i_BTN_SIZE + g_i_DISTANCE) * (2 - i) + g_i_DISPLAY_HEIGHT,
					g_i_BTN_SIZE, g_i_BTN_SIZE,
					hwnd,
					(HMENU)(number + 1000),
					GetModuleHandle(NULL),
					NULL
				);
				number++;
			}
		}
		/////////////////////////--0--//////////////////////////////////////////
		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X, g_i_START_Y + (g_i_BTN_SIZE + g_i_DISTANCE) * 3 + g_i_DISTANCE + g_i_DISPLAY_HEIGHT,
			g_i_BTN_SIZE * 2 + g_i_DISTANCE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL), NULL
		);
		////////////////////////--.--/////////////////////////////////////////////
		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 2,
			g_i_START_Y + (g_i_BTN_SIZE + g_i_DISTANCE) * 3 + g_i_DISTANCE + g_i_DISPLAY_HEIGHT,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL), NULL
		);
		/////////////////////////--/--//////////////////////////////////////
		CreateWindowEx
		(
			NULL, "Button", "/",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3,
			g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_SLASH,
			GetModuleHandle(NULL), NULL
		);
		////////////////////////--*--///////////////////////////////
		CreateWindowEx
		(
			NULL, "Button", "*",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3,
			g_i_START_Y + g_i_DISPLAY_HEIGHT + (g_i_DISTANCE * 2 + g_i_BTN_SIZE),
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_ASTER,
			GetModuleHandle(NULL), NULL
		);
		////////////////-//////////////////////////
		CreateWindowEx
		(
			NULL, "Button", "-",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3,
			g_i_START_Y + g_i_DISPLAY_HEIGHT + (g_i_DISTANCE * 3 + g_i_BTN_SIZE * 2),
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_MINUS,
			GetModuleHandle(NULL), NULL
		);

		/// /////////////--+--//////////////////

		CreateWindowEx
		(
			NULL, "Button", "+",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3,
			g_i_START_Y + g_i_DISPLAY_HEIGHT + (g_i_DISTANCE * 4 + g_i_BTN_SIZE * 3),
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_PLUS,
			GetModuleHandle(NULL), NULL
		);
		//////////////////--C--///////////////////////////
		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 4,
			g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE * 2 + g_i_DISTANCE,
			hwnd, (HMENU)IDC_BUTTON_CLEAR,
			GetModuleHandle(NULL), NULL
		);
		//////////////////////////////////
		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 4,
			g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_DISTANCE * 3 + g_i_BTN_SIZE * 2,
			g_i_BTN_SIZE, g_i_BTN_SIZE * 2 + g_i_DISTANCE,
			hwnd, (HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL), NULL
		);
		//////////////////////////////////
	}
	break;


	case WM_SIZE:
	case WM_MOVE:
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		//INT start_x = rect.left;
		//INT start_y = rect.top;
		INT width = rect.right - rect.left; //ширина право минус лево
		INT height = rect.bottom - rect.top;//высота дно-верх

		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		sprintf(sz_buffer, "%s,Size: %ix%i, Position:%ix%i", g_sz_MY_WINDOW_CLASS, rect.left, rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
	break;

	case WM_COMMAND:
	{
		//соотношение клавиш с цифрами при нажатии на клавишу высвечивается цифра или точка
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		CHAR sz_digit[2] = {};
		static double a=0;
		double b=0;//в b получаем число с экрана
		
		bool stored = false;
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			stored = false;
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			while (sz_buffer[0] == '0')
			{
				for (int i = 0; i < sz_buffer[i]; i++)
					sz_buffer[i] = sz_buffer[i + 1];
			}

			sz_digit[0] = LOWORD(wParam) - 1000 + '0';
			strcat(sz_buffer, sz_digit);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}

		if (LOWORD(wParam) == IDC_BUTTON_POINT)
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (strchr(sz_buffer, '.'))break;
			sz_digit[0] = '.';
			strcat(sz_buffer, sz_digit);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		if (LOWORD(wParam) == IDC_BUTTON_CLEAR)
		{
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"0");
		}

		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam <= IDC_BUTTON_SLASH))
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			b = strtod(sz_buffer, NULL);
			if (a == 0)
			{
				a = b;
				break;
			}
			switch (LOWORD(wParam))
			{
			case IDC_BUTTON_PLUS:a += b; break;
			case IDC_BUTTON_MINUS:a -= b; break;
			case IDC_BUTTON_ASTER:a *= b; break;
			case IDC_BUTTON_SLASH:a /= b; break;
			}
			stored = true;
			sprintf(sz_buffer, "%g", a);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
	}
	break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE:
		//if (MessageBox(hwnd, "вы действительно хотите закрыть окно?", "Question", MB_YESNO | MB_ICONQUESTION) == IDYES)

		DestroyWindow(hwnd); //уничтожает окно, хендлер которого передаём функции
		//конкретно здесь функция DestroyWindow посылает сообщение WM_DESTROY
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;


}
