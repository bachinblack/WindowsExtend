#pragma once

#include <Exec.hpp>

/* Hooks */

LRESULT CALLBACK KbProc(int code, WPARAM wp, LPARAM lp);
LRESULT CALLBACK MsProc(int code, WPARAM wp, LPARAM lp);

void setDesktopResolution(void);

/* Exec */

VOID Exec(LPCTSTR lpApplicationName);

/* NotifyIcon */

bool	CreateNotifyIcon(HINSTANCE& hInstance);
