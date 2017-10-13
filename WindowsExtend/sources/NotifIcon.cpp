#include <Windows.h>
#include <Strsafe.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	case WM_CONTEXTMENU:
	{
		POINT const pt = { LOWORD(wParam), HIWORD(wParam) };
		//ShowContextMenu(hwnd, pt);
		break;
	}
	return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool	CreateNotifyIcon(HINSTANCE& hInstance)
{
	NOTIFYICONDATA	notif = {};
	static const wchar_t class_name[] = L"ExtendClass";
	WNDCLASSEX wx = {};
	wx.cbSize = sizeof(WNDCLASSEX);
	wx.lpfnWndProc = WindowProc;        // function which will handle messages
	wx.hInstance = hInstance;
	wx.lpszClassName = class_name;

	RegisterClassEx(&wx);
	HWND win = CreateWindowEx(0, class_name, L"Windows Extend", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	if (win == NULL)
		OutputDebugStringW(L"failed to create window\n");
	ZeroMemory(&notif, sizeof(NOTIFYICONDATA));
	notif.cbSize = sizeof(NOTIFYICONDATA);
	notif.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	// Need to find a non-busy uID
	notif.uID = 42421;
	notif.hWnd = win;
	StringCchCopy(notif.szTip, ARRAYSIZE(notif.szTip), L"Access Windows Extend options.");
	StringCchCopy(notif.szInfo, ARRAYSIZE(notif.szInfo), L"Access Windows Extend options.");
	StringCchCopy(notif.szInfoTitle, ARRAYSIZE(notif.szInfoTitle), L"Windows Extend");
	notif.hIcon = (HICON)LoadImage(NULL, L"./Luma.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);

	if (!Shell_NotifyIcon(NIM_ADD, &notif))
	{
		return false;
		OutputDebugStringW(L"failed to create notifIcon\n");
	}
	return true;
}