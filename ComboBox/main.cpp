#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* values[] = { "This","is","my","First","Combo","Box" };//������ �����

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
		//������� ���� �������� ����� ���������� ���������
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		//��� ������ � �������� value ���������� ����. sizeof - ���������� ������ � ������
		//����� �� ������ �������� �������� � �������� ���������� ��������� �������
		//��������� �������� 4 ����� 6 ���� 24 �����
		for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)values[i]);//� hCombo ���������� 
			//��������� CB_ADDSTRING-������������ �������� � ��� ������������� �� ���� ������ 
			//������ � ������ ���� �� �������.
			// ���������� �� �������� ���������� � ���������� ���� Properties �������� Sort true ��� false
		}
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))//���� ��������� ������������� �������� ����������
		{
		case IDOK: //�� ������� �� ������ �� ���������� ��������� ��������
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);//getcursrl-���������� ����� 
			//���������� �������� ����������� ������
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);//����� ���������� �������� ������ ��� ������� i
			CHAR sz_message[SIZE] = {};//������ ������� ��������?

			sprintf(sz_message, "�� ������� ������� �%i, �� ��������� \"%s\"", i, sz_buffer);
			//������ ������� ��������������� ������
			//i- ����� ��� ���������� ���������, s-������ ��� ���������� ���������
			/*sprintf ������ ��������������� ������ � ������,
			 ������� ������ � ��� �� �������, ������� ��� �� ���������, ���� �� ������ ������������� � printf,
			 �� ������ ������ ���������� �������� � ���� C string � ������, �� ������� ��������� str.
			 ��������� �� ����� - sz_message, � ������� �������� �������������� C-������
			 ����� ������ ���� ���������� �������, ����� �������� �������������� ������.
			 ������ - ������ C, ���������� ������ ��������������, ������� ������������� ��� �� �������������,
			 ��� � ������ � printf(���� ���������� ������������� )
			... (�������������� ���������)
			� ����������� �� ������ ������� ������� ����� ������� ������������������ �������������� ����������, ������ ��
			������� �������� ��������, ������� ����� �������������� ��� ������ ������������� ������� � ������ ������� (���
			��������� �� ����� �������� ��� n).
			���� ���������� ������ ���� �� ������� ���� ������� ��, ������� ��������, ��������� � �������������� �������.
			�������������� ��������� ������������ ��������.*/

			MessageBox(hwnd, sz_message, "info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL: EndDialog(hwnd, 0); break;//�� ������� �� ������ cancel - �����
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
