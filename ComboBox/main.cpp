#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* values[] = { "This","is","my","First","Combo","Box" };//массив строк

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//MessageBox(NULL, "ComboBox check", "Info", MB_OK | MB_ICONINFORMATION);
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);//
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		//находим окно которому будем отправлять сообщения
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		//для работы с массивом value используем цикл. sizeof - возвращает размер в байтах
		//делим на размер нулевого злемента и получаем количество элементов массива
		//указатель занимает 4 байта 6 слов 24 байта
		for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)values[i]);//в hCombo отправляем 
			//сообщение CB_ADDSTRING-Возвращаемое значение — это отсчитываемый от нуля индекс 
			//строки в списке поля со списком.
			// сортировка по алфавиту включается в диалоговом окне Properties параметр Sort true или false
		}
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))//сюда прилетает идентификатор элемента интерфейса
		{
		case IDOK: //по нажатии на кнопку ОК выполнятся следующие действия
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);//getcursrl-определяем номер 
			//выбранного элемента выпадающего списка
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);//текст выбранного элемента списка под номером i
			CHAR sz_message[SIZE] = {};//массив который содержит?

			sprintf(sz_message, "Вы выбрали элемент №%i, со значением \"%s\"", i, sz_buffer);
			//второй элемент форматированная строка
			//i- число при выполнении программы, s-Строка при выполнении программы
			/*sprintf Запись форматированных данных в строку,
			 Создает строку с тем же текстом, который был бы напечатан, если бы формат использовался в printf,
			 но вместо печати содержимое хранится в виде C string в буфере, на который указывает str.
			 Указатель на буфер - sz_message, в котором хранится результирующая C-строка
			 Буфер должен быть достаточно большим, чтобы вместить результирующую строку.
			 формат - Строка C, содержащая строку форматирования, которая соответствует тем же спецификациям,
			 что и формат в printf(есть встроенные спецификаторы )
			... (дополнительные аргументы)
			В зависимости от строки формата функция может ожидать последовательность дополнительных аргументов, каждый из
			которых содержит значение, которое будет использоваться для замены спецификатора формата в строке формата (или
			указателя на место хранения для n).
			Этих аргументов должно быть по крайней мере столько же, сколько значений, указанных в спецификаторах формата.
			Дополнительные аргументы игнорируются функцией.*/

			MessageBox(hwnd, sz_message, "info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL: EndDialog(hwnd, 0); break;//по нажатии на кнопку cancel - выход
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
