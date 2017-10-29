#include "Data.hpp"
#include "WindowsExtend.hpp"

//	OutputDebugStringW(L"Start.\n");
//Exec(L"C:/Program Files (x86)/Google/Chrome/Application/chrome.exe");

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR pCmdLine, int nCmdShow)
{
	Data data(hInst);
	MSG msg;

	while (GetMessageW(&msg, NULL, NULL, NULL) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}