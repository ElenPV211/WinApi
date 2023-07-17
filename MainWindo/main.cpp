#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_MY_WINDOW_CLASS[] = "MyFirstWindow";

INT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);//��������� ����

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR IpCmdLine, INT nCmdShow)
{
	//1.����������� ������ ����
	 WNDCLASSEX wc; //��������� ����� ��������� WNDCLASSEX � ������ wc
	 //�������� ��������� ������ ���� wc ��������
	 ZeroMemory(&wc, sizeof(wc));

     //�������������� ��������� ������
	 //���� ��������� � ���������
	 wc.cbSize = sizeof(wc); //������ ������ � ������ cb-Count Bytes
	 wc.cbClsExtra = 0; //Class ExtraBytes �������������� ����� ������
	 wc.cbWndExtra = 0; //WindowExtraBytes �������������� ����� ����
	 wc.style = 0;

	 //������� ��� ����, ������ � �������, �� �� ����� ���������
	// wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_TREE));//������������ � ������ �����
	 //wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_jupiter));//������������ � ��������� ����
	
	 wc.hIcon = (HICON)LoadImage(hInstance, "tree.ico",IMAGE_ICON,LR_DEFAULTSIZE,LR_DEFAULTSIZE,LR_LOADFROMFILE);
	 wc.hIconSm = (HICON)LoadImage(hInstance, "jupiter.ico",IMAGE_ICON,LR_DEFAULTSIZE,LR_DEFAULTSIZE,LR_LOADFROMFILE);

	 wc.hCursor = (HCURSOR)LoadImage(hInstance, "Normal.ani",IMAGE_CURSOR,LR_DEFAULTSIZE,LR_DEFAULTSIZE,LR_LOADFROMFILE);
	 wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	 wc.hInstance = hInstance;
	 wc.lpfnWndProc = (WNDPROC)WndProc; //��������� ����
	 wc.lpszMenuName = NULL;
	 wc.lpszClassName = g_sz_MY_WINDOW_CLASS;//������ ��� ������� ������� ������ ����� �� ���������������
	 //lpsz(long pointer saiz zero) - ��������� �� ������


	 //������� ��� ����������� ��������� RegisterClassEx. �������� ��������������� �� �����
	 if (!RegisterClassEx(&wc))
	 {
		 MessageBox(NULL, "����� �� ���������������", "Error", MB_OK | MB_ICONERROR);
		 return 0;
	 }
	//2 �������� ����
	 //�������� ������� CreateWindowEx
	 HWND hwnd = CreateWindowEx
	 (
		 0,
		 g_sz_MY_WINDOW_CLASS,//��� ������ ���� 
		 g_sz_MY_WINDOW_CLASS,//��������� ����
		 WS_OVERLAPPEDWINDOW,//�� ����� ���� �������� ����� ���� � ��� ������� ������ ���� ���� ����� ������
		//�� ������� ���� ��� ������ ��� ���� ����, ����� ���� ������������ ��� �������
//����� ���� ��� �������� ���� ��������� ������ ����� WS_OVERLAPPEDWINDOW
		//WS_OVERLAPPEDWINDOW - ��� ���� �������� ������ (TOP_LEVEL_WINDOW), ������� �������� � ���� �������� ���� (CHILDWINDOW)
	
		 CW_USEDEFAULT,CW_USEDEFAULT, //��������� ������� ���� (�,� ��������� �� ������)
		 CW_USEDEFAULT,CW_USEDEFAULT, //������ ���� (������, ������)
		 NULL,//������������ ����, Parametr Window
		 NULL,//��� �������� ���� ��� ����, ��� ��������� ���� ��� ID ��� �������
		 hInstance,
		 NULL		
	 );
	 if (hwnd == 0)
	 {
		 MessageBox(NULL, "���� �� ���� �������", "Error", MB_OK | MB_ICONERROR);
		 return 0;
	 }
	 ShowWindow(hwnd, nCmdShow);//����� ����� ����������� ����
	 UpdateWindow(hwnd);//��������� ���������� ����

	//3. ������ ����� ����������

MSG msg;
while (GetMessage(&msg, NULL, 0, 0) > 0)
{
	TranslateMessage(&msg);//����������� ��������� ����������� ������ � ���������� ���������
	DispatchMessage(&msg); //���������� ��������� � ��������� ���� ��������� ���� �� GetMessage
	//������� �������� ��������� �� ������� msg
}
return msg.wParam;
}





INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE: //
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE:	
		if (MessageBox(hwnd, "�� ������������� ������ ������� ����?", "Question", MB_YESNO | MB_ICONQUESTION) == IDYES)
		
		DestroyWindow(hwnd); //���������� ����, ������� �������� ������� �������
		//��������� ����� ������� DestroyWindow �������� ��������� WM_DESTROY
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;

	
}
