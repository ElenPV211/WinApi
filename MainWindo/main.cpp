#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR g_sz_MY_WINDOW_CLASS[] = "MyFirstWindow";

INT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);//процедура окна

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
	
	 wc.hIcon = (HICON)LoadImage(hInstance, "tree.ico",IMAGE_ICON,LR_DEFAULTSIZE,LR_DEFAULTSIZE,LR_LOADFROMFILE);
	 wc.hIconSm = (HICON)LoadImage(hInstance, "jupiter.ico",IMAGE_ICON,LR_DEFAULTSIZE,LR_DEFAULTSIZE,LR_LOADFROMFILE);

	 wc.hCursor = (HCURSOR)LoadImage(hInstance, "Normal.ani",IMAGE_CURSOR,LR_DEFAULTSIZE,LR_DEFAULTSIZE,LR_LOADFROMFILE);
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

	 INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	 INT screen_height = GetSystemMetrics(SM_CYSCREEN);

	 INT window_width = screen_width * 3 / 4;
	 INT window_height = screen_height * 3 / 4;

	 INT start_x = screen_width / 8;
	 INT start_y = screen_height / 8;


	 HWND hwnd = CreateWindowEx
	 (
		 0,
		 g_sz_MY_WINDOW_CLASS,//имя класса окна 
		 g_sz_MY_WINDOW_CLASS,//заголовок окна
		 WS_OVERLAPPEDWINDOW,//за стиль окна отвечает класс окна и для каждого класса есть свой набор стилей
		//вы создаёте окно или кнопку или дрек даун, стиль окна определяется его классом
//Стиль окна для главного окна программы всегда будет WS_OVERLAPPEDWINDOW
		//WS_OVERLAPPEDWINDOW - это окно верхнего уровня (TOP_LEVEL_WINDOW), которое включает в себя дочерние окна (CHILDWINDOW)
	
		 start_x,start_y, //начальная позиция окна (х,у положение на экране)
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
	case WM_CREATE: //
		break;
	
	case WM_SIZE:
	case WM_MOVE:
	{
		RECT rect;
		GetWindowRect(hwnd,&rect);
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
		break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE:	
		if (MessageBox(hwnd, "вы действительно хотите закрыть окно?", "Question", MB_YESNO | MB_ICONQUESTION) == IDYES)
		
		DestroyWindow(hwnd); //уничтожает окно, хендлер которого передаём функции
		//конкретно здесь функция DestroyWindow посылает сообщение WM_DESTROY
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;

	
}
