#include "WindowsExtend.hpp"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR pCmdLine, int nCmdShow)
{
	HHOOK kHook = SetWindowsHookEx(WH_KEYBOARD_LL, KbProc, NULL, NULL);
	MSG msg;

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(kHook);
	return 0;
}
