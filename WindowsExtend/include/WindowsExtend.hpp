#pragma once

#include <Windows.h>

LRESULT CALLBACK KbProc(int code, WPARAM wp, LPARAM lp);
LRESULT CALLBACK MsProc(int code, WPARAM wp, LPARAM lp);

void setDesktopResolution(void);
