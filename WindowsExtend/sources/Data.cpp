#include "Data.hpp"

Data::Data(HINSTANCE& hInst)
{
	OutputDebugStringW(L"Creating everything.\n");
	_kHook = SetWindowsHookEx(WH_KEYBOARD_LL, KbProc, NULL, NULL);
	_mHook = SetWindowsHookEx(WH_MOUSE_LL, MsProc, NULL, NULL);
	CreateNotifyIcon(hInst);
	setDesktopResolution();
}

Data::~Data()
{
	OutputDebugStringW(L"Deleting everything.\n");
	Shell_NotifyIcon(NIM_DELETE, &_notif);
	UnhookWindowsHookEx(_kHook);
	UnhookWindowsHookEx(_mHook);
}
