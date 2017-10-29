#pragma once

#include <Windows.h>
#include "WindowsExtend.hpp"

class Data
{
public:
	Data(HINSTANCE& hInst);
	~Data();
private:
	NOTIFYICONDATA  _notif;
	HHOOK			_mHook;
	HHOOK			_kHook;
};