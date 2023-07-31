#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR g_sz_MY_WINDOW_CLASS[] = "MyFirstWindow";

//g-global i-int
CONST INT g_i_BTN_SIZE = 50; //размер кнопки
CONST INT g_i_DISTANCE = 10;  //расстояние между кнопками
CONST INT g_i_START_X = 10;  //отступ от начала окна
CONST INT g_i_START_Y = 10;  //отступ от начала окна
CONST INT g_i_DISPLAY_WIDTH = g_i_BTN_SIZE * 5 + g_i_DISTANCE * 4; //ширина окошка дисплея
CONST INT g_i_DISPLAY_HEIGHT = 32;//высота окошка дисплея
CONST char g_sz_DISPLAY_FONT[] = "Arial";
CONST INT g_i_DISPLAY_FONT_HEIGHT = g_i_DISPLAY_HEIGHT - 2;
CONST INT g_i_DISPLAY_FONT_WIDTH = g_i_DISPLAY_FONT_HEIGHT / 2.5;

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//процедура окна

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wc; //объявляем класс структуры WNDCLASSEX с именем wc
	ZeroMemory(&wc, sizeof(wc));//зануляем экземпляр класса окна wc

	//инициализируем экземпляр класса, 
	//размеры, всё ззануляем
	wc.cbSize = sizeof(wc);	//Размер класса в Байтах (cb - Count Bytes)
	wc.cbClsExtra = 0;		//Class ExtraBytes дополнительные Байты класса
	wc.cbWndExtra = 0;		//WindowExtraBytes дополнительные Байты окна
	wc.style = 0;           //стиль - 

	//настраиваем внешний вид окна, иконки и курсоры, мы можем загрузить их сами
//	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);//отбражение стандартной иконки
	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_STARS));//проводим явное преобразование в HICON
	//иконка hIcon-отображается на панели задач
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_UMBRELLA));//отображается в заголовке окна
	//функция LoadImage Загружает значок, курсор, анимированный курсор или растровое изображение.
	wc.hIcon = (HICON)LoadImage(hInstance, "umbrella.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE/*ширина*/, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "stars.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);

	//wc.hCursor = LoadCursor(hInstance, IDC_ARROW);//стандартный вызов курсора
	wc.hCursor = (HCURSOR)LoadImage(hInstance, "Busy.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);

	//wc.hbrBackground = (HBRUSH)COLOR_WINDOW; //цвет окна стандарт
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 200));

	//
	wc.hInstance = hInstance;
	wc.lpfnWndProc = (WNDPROC)WndProc;//процедура окна
	wc.lpszMenuName = NULL;  //
	wc.lpszClassName = g_sz_MY_WINDOW_CLASS;//строка без которой выходит ошибка класс не зарегистрирован
	//lpsz(long pointer saiz zero) - указатель на строку

	//функция для регистрации RegisterClassEx. проверка зарегестрирован ли класс
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Класс не зарегистрирован", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}//2) Создание окна

	INT screen_width = GetSystemMetrics(SM_CXSCREEN);//ч/з функцию мы можем получить интересующие нас параметры, 
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);//SM_CYSCREEN-Высота экрана основного монитора в пикселях.

	//INT window_width = screen_width * 3 / 4;//ширина //размер созданного окна занимает 3/4 от экрана компьютера
	//INT window_height = screen_height * 3 / 4;//высота
	INT window_width = g_i_START_X * 2 + g_i_DISPLAY_WIDTH + g_i_DISTANCE * 2;
	INT window_height = g_i_START_Y * 2 + g_i_DISPLAY_HEIGHT + (g_i_BTN_SIZE * 5 + g_i_DISTANCE * 3);

	INT start_x = screen_width / 8;
	INT start_y = screen_height / 8;
	//
	//для того чтобы нельзя было изменять окошко по размерам посмотрим стили окна


	//вызываем функцию CreateWindowEx
	HWND hwnd = CreateWindowEx
	(
		0,
		g_sz_MY_WINDOW_CLASS,	//Имя класса окна
		g_sz_MY_WINDOW_CLASS,	//Заголовок окна
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		//WS_OVERLAPPEDWINDOW,	//за стиль окна отвечает класс окна и для каждого класса есть свой набор стилей
		//вы создаёте окно или кнопку или дрек даун, стиль окна определяется его классом
		//Стиль окна для главного окна программы всегда будет WS_OVERLAPPEDWINDOW
		//WS_OVERLAPPEDWINDOW - это окно верхнего уровня (TOP_LEVEL_WINDOW), которое включает в себя дочерние окна (CHILDWINDOW)
		start_x, start_y,	//Начальная позиция окна (х,у положение на экране)
		window_width, window_height, 	//Размер окна (ширина, высота)
		NULL,	//Родительское окно, Parent Window
		NULL,	//Для главного окна это меню, для дочернего окна это ID его ресурса (IDC_EDIT)
		//при помощи этой штуки мы можем найти в окне при помощи GetDlgItem(оно работает не только в диалоговых но и обычных окнах
		hInstance,
		NULL
	);

	if (hwnd == 0)
	{
		MessageBox(NULL, "Окно не было создано", "Error", MB_OK | MB_ICONERROR);

		return 0;
	}
	ShowWindow(hwnd, nCmdShow);//задаёт режим отображения окна, свёрнуто, развёрнуто
	UpdateWindow(hwnd);//выполняет прорисовку окна

	//3) Запуск цикла сообщений
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
		//пока в цикле есть сообщения > 0, цикл работает
	{
		TranslateMessage(&msg);//транслирует сообщение виртуальных клавиш в символьные сообщения
		DispatchMessage(&msg); //отправка сообщения процедуре окна. Сообщение берёт от GetMessage
		//он достает первое сообщение из очереди в msg и отправляет в процедуру окна
	}
	return msg.wParam;
}

//процедура самого обычного окна
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//SetFocus(hwnd);
	switch (uMsg) //по значению переменной выбирает один из множества вариантов кода
	{
	case WM_CREATE://аналог wm_create dialog сообщение wm_create посылается один
		//единственный раз	//здесь мы можем создавать какие то элементы окна
	{
		//создаём дочерние окна
		HWND hEdit = CreateWindowEx
		(
			NULL, // exStyle
			"Edit",	//имя класса g_sz_MY_WINDOW_CLASS, если мы хотим создать едит бокс то указываем 
			//такое название, которое мы можем найти в характеристиках CreateWindowEx
			// Имя класса может быть любым именем, зарегистрированным в RegisterClass или RegisterClassEx
			//, при условии, что модуль, регистрирующий класс, также является модулем, создающим окно. 
			//Имя класса также может быть любым из предопределенных имен системных классов.
			//системные классы, доступные для использования всеми процессами.
			//Имя окна.
			"0",//"0"-появится нолик при запуске окна
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT /* | ES_READONLY*/, //стили окна //WS_CHILD - Окно является дочерним окном. Окно с таким стилем не может иметь строку меню. 
			//| WS_VISIBLE - Окно изначально видно.| ES_RIGHT-  выравнивание по правому краю
			g_i_START_X, g_i_START_Y,//координаты начала, относительно начала окна
			g_i_DISPLAY_WIDTH, g_i_DISPLAY_HEIGHT,//размер окна
			hwnd, //родительское окно
			(HMENU)IDC_EDIT,//Для главного окна это меню, для дочернего окна это ID его ресурса (IDC_EDIT)
			GetModuleHandle(NULL),//hInstance получаем по функции GetModuleHandle(NULL)
			NULL
		);
		/*LOGFONT lFont;
		ZeroMemory(&lFont, sizeof(LOGFONT));
		lFont.lfCharSet = DEFAULT_CHARSET;
		lFont.lfHeight = -20;
		HFONT hFont = CreateFontIndirect(&lFont);*/
		HFONT hFont = CreateFont
		(g_i_DISPLAY_FONT_HEIGHT,g_i_DISPLAY_FONT_WIDTH,//высота ширина шрифта
			GM_ADVANCED,0,600,//Escapement, Oriental, Weight - толщина шрифта
			FALSE,FALSE,FALSE, //Itlic -курсив,Underline - подчёркивание,Strikeout - перечёркнутый
			DEFAULT_CHARSET, //кодировка
			OUT_CHARACTER_PRECIS,
            CLIP_CHARACTER_PRECIS,
			ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			g_sz_DISPLAY_FONT
			);
		SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
		
	

		//создание окон в цикле
		CHAR sz_btn_name[] = "0";
		INT number = 1;
		//через i, j определяем координаты кнопок
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				//https://learn.microsoft.com/en-us/windows/win32/controls/button-styles
				sz_btn_name[0] = number + 48; //начинаем нумерацию с единицы, 48 это  на аски коде '0', 49 это 1
				HWND hButtonDigit = CreateWindowEx
				(
					NULL,
					"Button",
					sz_btn_name,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON |BS_ICON,//стили
					g_i_START_X +/*g_i_DISTANCE +*/ (g_i_BTN_SIZE + g_i_DISTANCE) * j,
					g_i_START_Y + g_i_DISTANCE + (g_i_BTN_SIZE + g_i_DISTANCE) * (2 - i) + g_i_DISPLAY_HEIGHT,
					g_i_BTN_SIZE, g_i_BTN_SIZE,
					hwnd,
					(HMENU)(number + 1000),
					GetModuleHandle(NULL),//hInstance получаем
					NULL
				);
				SendMessage(hButtonDigit, BM_SETIMAGE, IMAGE_ICON,
					(LPARAM)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(number + 200))
				);
				number++;
			}
		}
		/////////////////////////------0--//////////
		HWND hBtnNULL = CreateWindowEx
		(
			NULL, "Button", "0"/*WindowName*/,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
			g_i_START_X, g_i_START_Y + g_i_BTN_SIZE * 3 + g_i_DISTANCE * 4 + g_i_DISPLAY_HEIGHT,
			g_i_BTN_SIZE * 2 + g_i_DISTANCE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL), NULL
		);
		HICON hIconNULL = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_0));//вместо IDI_ICON_0 можно 200, работает
		SendMessage(hBtnNULL, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIconNULL);

		/////////////////////////-----.--//////////
		HWND hBtnPoint = CreateWindowEx
		(
			NULL, "Button", "."/*WindowName*/,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
			g_i_START_X + g_i_BTN_SIZE * 2 + g_i_DISTANCE * 2, g_i_START_Y + g_i_BTN_SIZE * 3 + g_i_DISTANCE * 4 + g_i_DISPLAY_HEIGHT,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL), NULL
		);
		HICON hIconPoint = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_POINT));
		SendMessage(hBtnPoint, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIconPoint);


		/////////////////////////------/----//////////
		HWND hBtnSlash = CreateWindowEx
		(
			NULL, "Button", "/"/*WindowName*/,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3, g_i_START_Y + g_i_DISTANCE + g_i_DISPLAY_HEIGHT,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_SLASH,
			GetModuleHandle(NULL), NULL
		);
		HICON hIconSlash = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_SLASH));
		SendMessage(hBtnSlash, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIconSlash);

		/////////////////////////------*----//////////
		HWND hBtnAster = CreateWindowEx
		(
			NULL, "Button", "*"/*WindowName*/,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3, g_i_START_Y + g_i_BTN_SIZE + g_i_DISTANCE * 2 + g_i_DISPLAY_HEIGHT,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_ASTER,
			GetModuleHandle(NULL), NULL
		);
		HICON hIconAster = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_TREE));//на место звездочки устанавливается иконка
		SendMessage(hBtnAster, BM_SETIMAGE, IMAGE_ICON,(LPARAM)hIconAster);
		/////////////////////////-----/-/----//////////
		HWND hBtnMinus = CreateWindowEx
		(
			NULL, "Button", "-"/*WindowName*/,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3, g_i_START_Y + g_i_BTN_SIZE * 2 + g_i_DISTANCE * 3 + g_i_DISPLAY_HEIGHT,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_MINUS,
			GetModuleHandle(NULL), NULL
		);
		HICON hIconMinus = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_MINUS));
		SendMessage(hBtnMinus, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIconMinus);

		/////////////////////////-----+----//////////
		HWND hBtnPlus = CreateWindowEx
		(
			NULL, "Button", "+"/*WindowName*/,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3, g_i_START_Y + g_i_BTN_SIZE * 3 + g_i_DISTANCE * 4 + g_i_DISPLAY_HEIGHT,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_PLUS,
			GetModuleHandle(NULL), NULL
		);
		HICON hIconPlus = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_PLUS));
		SendMessage(hBtnPlus, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIconPlus);

		/////////////////////////------C----//////////
		HWND hBtnClear = CreateWindowEx
		(
			NULL, "Button", "C"/*WindowName*/,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 4, g_i_START_Y + g_i_DISTANCE + g_i_DISPLAY_HEIGHT,
			g_i_BTN_SIZE, g_i_BTN_SIZE * 2 + g_i_DISTANCE,
			hwnd, (HMENU)IDC_BUTTON_CLEAR,
			GetModuleHandle(NULL), NULL
		);
		HICON hIconClear = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_CLEAR));
		SendMessage(hBtnClear, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIconClear);

		/////////////////////////------=----//////////
		HWND hBtnEqual = CreateWindowEx
		(
			NULL, "Button", "="/*WindowName*/,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 4, g_i_START_Y + g_i_DISTANCE * 3 + g_i_BTN_SIZE * 2 + g_i_DISPLAY_HEIGHT,
			g_i_BTN_SIZE, g_i_BTN_SIZE * 2 + g_i_DISTANCE,
			hwnd, (HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL), NULL
		);
		HICON hIconEqual = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_EQUAL));
		SendMessage(hBtnEqual, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIconEqual);

	}
	break;
	case WM_CTLCOLOREDIT:
	{
		//меняем шрифт
		HDC hdc = (HDC)wParam;
		SetBkMode(hdc, OPAQUE);
		SetBkColor(hdc, RGB(0, 0, 100));
		HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
		SetTextColor(hdc, RGB(255, 0, 0));
		return (LRESULT)hBrush;
	}
	break;
	case WM_SIZE://размер окна
	case WM_MOVE://кейс про перемещение
	{
		RECT rect; //прямоугольник
		GetWindowRect(hwnd, &rect); //получаем прямоугольник окна
		//&rect - взятие адреса в памяти 'rect'

		//top - содержит координату окна по у(верх), bottom - по у (низ), 
		//left, right по х
		//INT start_x = rect.left;
		//INT start_y = rect.top;
		INT width = rect.right - rect.left;
		INT height = rect.bottom - rect.top;

		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};

		sprintf(sz_buffer, "%s, Size: %ix%i, Position: %ix%i", g_sz_MY_WINDOW_CLASS, width, height, rect.left, rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
	break;
	case WM_COMMAND:
	{

		//соотношение клавиш с цифрами при нажатии на клавишу высвечивается цифра или точка
		SetFocus(hwnd);
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		CHAR sz_digit[2] = {};
		static double a = 0;
		static double b = 0; //в а - мы будем хранить результаты, в b - будем получать число с экрана
		static bool stored = false;
		static bool input = false;
		static bool operation_input = false;
		static char operation = 0;
		static char old_operation = 0;

		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			input = true;
			if (stored)
			{
				SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"");
				stored = false; //если мы ввели хотя бы одну цифру

			}
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);//прочитали буфер
			while (sz_buffer[0] == '0')//при добавлении цифр, 0 по умолчанию убирается
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
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);//прочитали буфер
			if (strchr(sz_buffer, '.'))break;//strchr-проверка есть ли в буфере точка
			sz_digit[0] = '.';
			strcat(sz_buffer, sz_digit);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		if (LOWORD(wParam) == IDC_BUTTON_CLEAR)
		{
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"0");//устанавливаем ноль в экран
			a=b = 0;
			stored = false;
			input = false;
			operation_input = false;
			operation = 0;
			//SetFocus(hwnd);
		}

		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam <= IDC_BUTTON_SLASH))
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (input)b = strtod(sz_buffer, NULL);//strtod возвращает значение числа с плавающей запятой
			if (a == 0)		a = b;
			stored = true;
			if (input && operation_input)//усли вводилась и цифра и операция
			{
				SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0);
				//operation_changed = false;
			}
			input = false;
			switch (LOWORD(wParam))
			{
			case IDC_BUTTON_PLUS:	operation = '+'; break;
			case IDC_BUTTON_MINUS:	operation = '-'; break;
			case IDC_BUTTON_ASTER:	operation = '*'; break;
			case IDC_BUTTON_SLASH:	operation = '/'; break;
			}
			operation_input = true;
		}


		if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (input)	b = strtod(sz_buffer, NULL);
			input = false;


			switch (operation)
			{
			case '+': a += b; break;
			case '-': a -= b; break;
			case '*': a *= b; break;
			case '/': a /= b; break;
			}
			//old_operation = operation;
			operation_input = false;//после выполнения операции сбрасываем триггер
			sprintf(sz_buffer, "%g", a);//преобразовать число в строку и загоняем в буфер а
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer); //результат отображаем на экране когда
			//нажимается знак равенства
			// операцию тоже надо будет запоминать для знака

		}
	}
	break;
	//функция create - создаёт окно и возвращает хендлер этого окна 
		//по хендлеру мы можем обратиться к окну
	case WM_KEYDOWN:
	{
		//char symbol[2];		
		//symbol[0] = LOWORD(wParam);
		//MessageBox(hwnd, symbol, "Symbol", MB_OK);
		if (GetKeyState(VK_SHIFT) < 0)
		{
			if(wParam==0x38)SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0);
		}
		else
		{
			if (LOWORD(wParam) >= '0' && LOWORD(wParam) <= '9')
				SendMessage(hwnd, WM_COMMAND, LOWORD(wParam) - '0' + 1000, 0);
		}
		if (LOWORD(wParam) >= 0x60 && LOWORD(wParam) <= 0x69)
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParam) - 0x60 + 1000, 0);
		switch (wParam)
		{
		case VK_ADD:case VK_OEM_PLUS:  SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_PLUS, 0); break;
		case VK_SUBTRACT: case VK_OEM_MINUS: SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_MINUS, 0); break;
		case VK_MULTIPLY: SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0); break;
		case VK_OEM_2: 	case VK_DIVIDE: SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_SLASH, 0); break;
		case VK_RETURN: SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0); break;
		case VK_ESCAPE: SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_CLEAR, 0); break;
		}
		if (wParam == VK_OEM_PERIOD||wParam==VK_DECIMAL)SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_POINT, 0);

		
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0); //по факту окно уничтожается этой функцией
		break;
	case WM_CLOSE:
		//при нажатии на крестик выпадает окно, и при нажатии на да в новом окне закрывается оба окна вызовом функции DestroyWindow
		//if (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Question", MB_YESNO | MB_ICONQUESTION) == IDYES)
		DestroyWindow(hwnd); //destroy window - функция уничтожает окно и мы ему передаём хендлер этого окна
		//очистка памяти, уничтожает окно и освобождает ресурсы занимаемые этим окном
		//Конкретно здесь, функция DestroyWindow() посылает окну вообщение WM_DESTROY
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
