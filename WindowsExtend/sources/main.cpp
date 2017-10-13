#include "WindowsExtend.hpp"

//	OutputDebugStringW(L"Start.\n");
//Exec(L"C:/Program Files (x86)/Google/Chrome/Application/chrome.exe");

static bool InitValues(HHOOK& kHook, HHOOK& mHook, HINSTANCE& hInstance)
{
	setDesktopResolution();
	CreateNotifyIcon(hInstance);
	return true;
	kHook = SetWindowsHookEx(WH_KEYBOARD_LL, KbProc, NULL, NULL);
	mHook = SetWindowsHookEx(WH_MOUSE_LL, MsProc, NULL, NULL);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR pCmdLine, int nCmdShow)
{
	HHOOK kHook;
	HHOOK mHook;
	MSG msg;

	if (!InitValues(kHook, mHook, hInst))
		return EXIT_FAILURE;
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(kHook);
	UnhookWindowsHookEx(mHook);
	return 0;
}