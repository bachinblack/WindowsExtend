#include "WindowsExtend.hpp"

//	OutputDebugStringW(L"Start.\n");

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR pCmdLine, int nCmdShow)
{
	setDesktopResolution();
	HHOOK kHook = SetWindowsHookEx(WH_KEYBOARD_LL, KbProc, NULL, NULL);
	HHOOK mHook = SetWindowsHookEx(WH_MOUSE_LL, MsProc, NULL, NULL);
	MSG msg;

	//SetCursorPos(50, 50);
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(kHook);
	UnhookWindowsHookEx(mHook);
	return 0;
}
