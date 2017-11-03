#pragma once

#include <Windows.h>
#include "shortcut.h"

enum EnActive
{
    ALL = 0,
    CONV = 1,
    EXTS = 2,
    INVX = 3,
    INVY = 4,
    SC = 5
};

class Input
{
public:
    Input();
    ~Input();
    Shortcut *getSC(void) const;

private:
    static Shortcut *sc;
    HHOOK			_mHook;
    HHOOK			_kHook;

    /* Hooks */
private:
    static LRESULT CALLBACK KbProc(int code, WPARAM wp, LPARAM lp);
    static LRESULT CALLBACK MsProc(int code, WPARAM wp, LPARAM lp);
    bool   _disable;

private:
    /* Hooks subfunctions - keyboard */
    static bool convertQA(const PKBDLLHOOKSTRUCT& p, bool& wasSent);
    static void handleShortcuts(const DWORD& code, const WPARAM& wp);

    /* Hooks subfunctions - mouse */
    static bool ExtendScreen(POINT& pos);
    static void InvertX(POINT& pos);
    static void InvertY(POINT& pos);

public:
    void Disable(void);
    void Enable(void);

private:
    void setDesktopResolution(void);
};
