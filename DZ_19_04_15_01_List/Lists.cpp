/* 1. В клиентской области окна приложения создать 2 списка,
первый из которых содержит числа от 1 до 5, второй – числа от 200 до 205.
При нажатии кнопки «Добавить» в список с фокусом ввода добавить очередное число.*/

#include<Windows.h>
#include<tchar.h>

#define ID_LISTBOX1 1001
#define ID_LISTBOX2 1002
#define ID_BUTTON1 1010

static TCHAR WindowsClass[] = L"win32app";
static TCHAR Title[] = L"MyApp";
HINSTANCE hinst;
RECT desktop;
RECT cr;

HWND list1, list2, button1;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);*/
	wcex.hbrBackground = CreateSolidBrush(RGB(150, 70, 150));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Call faild!", L"MyApp", NULL);
		return 1;
	}

	hinst = hinstance;
	GetWindowRect(GetDesktopWindow(), &desktop);
	HWND hWnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPEDWINDOW,
		desktop.right / 4,
		desktop.bottom / 6,
		desktop.right / 2,
		desktop.bottom / 2,
		NULL,
		NULL,
		hinst,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL, L"Create window faild!", L"MyApp", NULL);
		return 1;
	}
	SetTimer(hWnd, 1, 100, NULL);
	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{

	case WM_COMMAND:

	case BN_CLICKED:
		
		break;
		
	case WM_CREATE:

		GetClientRect(hWnd, &cr);

		list1 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"listbox",
			L"",
			WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL | LBS_SORT,
			cr.right / 5,
			cr.bottom / 5,
			cr.right / 5,
			cr.bottom / 2,
			hWnd,
			(HMENU)ID_LISTBOX1,
			hinst,
			NULL);

		list2 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"listbox",
			L"",
			WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL | LBS_SORT,
			cr.right / 5 * 3,
			cr.bottom / 5,
			cr.right / 5,
			cr.bottom / 2,
			hWnd,
			(HMENU)ID_LISTBOX2,
			hinst,
			NULL);

		button1 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"button",
			L"Добавить",
			WS_CHILD | WS_VISIBLE,
			cr.right / 2 - 8 * 6,
			cr.bottom - 50,
			80,
			30,
			hWnd,
			(HMENU)ID_BUTTON1,
			hinst, NULL);
				
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}