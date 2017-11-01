#pragma once

#include <Windows.h>

enum EnActive
{
    ALL = 0,
    CONV = 1,
    EXTS = 2,
    INVX = 3,
    INVY = 4,
    INVXY = 5
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
    static bool ExtendScreen(const PMSLLHOOKSTRUCT& pmhs);
    static void InvertX(const PMSLLHOOKSTRUCT& pmhs);
    static void InvertY(const PMSLLHOOKSTRUCT& pmhs);

public:
    void Disable(void);
    void Enable(void);

private:
    void setDesktopResolution(void);
};
