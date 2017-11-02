#pragma once

#include <Windows.h>

enum EnActive
{
    ALL = 0,
    CONV = 1,
    EXTS = 2,
    INVX = 3,
    INVY = 4
};

class Input
{
public:
    Input();
    ~Input();
private:
    HHOOK			_mHook;
    HHOOK			_kHook;

    /* Hooks */
private:
    static LRESULT CALLBACK KbProc(int code, WPARAM wp, LPARAM lp);
    static LRESULT CALLBACK MsProc(int code, WPARAM wp, LPARAM lp);

private:
    /* Hooks subfunctions - keyboard */
    static bool convertQA(const PKBDLLHOOKSTRUCT& p, bool& wasSent);

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
