#include "inputs.h"
#include <qDebug>

static POINT screenSize;

static bool Active[5] = {false, false, false, false, false};

static unsigned char	qwerty[2][26] =
{
    {
        'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
        'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M',
        'W', 'X', 'C', 'V', 'B', 'N'
    },
    {
        'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
        'Z', 'X', 'C', 'V', 'B', 'N', 'M'
    }
};

Input::Input()
{
    setDesktopResolution();
    Enable();
}

Input::~Input()
{
    Disable();
}

bool Input::convertQA(const PKBDLLHOOKSTRUCT& p, bool& wasSent)
{
    for (unsigned char i = 0; i < 26; ++i)
    {
        if (p->vkCode == qwerty[0][i])
        {
            wasSent = true;
            keybd_event(qwerty[1][i], 0, 0, 0);
            return true;
        }
    }
    return false;
}

LRESULT CALLBACK Input::KbProc(int code, WPARAM wp, LPARAM lp)
{
    static bool wasSent = FALSE;
    PKBDLLHOOKSTRUCT	p;

    if (Active[ALL]) { return CallNextHookEx(NULL, code, wp, lp); }
    /* Getting only "down" events */
    if ((wp == WM_KEYDOWN || wp == WM_SYSKEYDOWN) && code == HC_ACTION)
    {
        if (wasSent == true)
        {
            wasSent = false;
            return CallNextHookEx(NULL, code, wp, lp);
        }
        p = (PKBDLLHOOKSTRUCT)lp;

        if (Active[CONV] && convertQA(p, wasSent))
            return 1;
    }
    return CallNextHookEx(NULL, code, wp, lp);
}

bool Input::ExtendScreen(const PMSLLHOOKSTRUCT& pmhs)
{
    POINT           p;

    p = pmhs->pt;
    if (pmhs->pt.x <= 2)
        pmhs->pt.x = screenSize.x;
    else if (pmhs->pt.x >= screenSize.x)
        pmhs->pt.x = 3;

    if (pmhs->pt.y <= 2)
        pmhs->pt.y = screenSize.y;
    else if (pmhs->pt.y >= screenSize.y)
        pmhs->pt.y = 3;

    SetCursorPos(pmhs->pt.x, pmhs->pt.y);
    if (p.x != pmhs->pt.x || p.y != pmhs->pt.y)
        return true;
    return false;
}

void Input::InvertX(const PMSLLHOOKSTRUCT& pmhs)
{

}

void Input::InvertY(const PMSLLHOOKSTRUCT& pmhs)
{

}

LRESULT CALLBACK Input::MsProc(int code, WPARAM wp, LPARAM lp)
{
    PMSLLHOOKSTRUCT	pmhs;

    if (Active[ALL]) { qDebug() << "disabled"; return CallNextHookEx(NULL, code, wp, lp); }
    if (code == HC_ACTION && wp == WM_MOUSEMOVE)
    {
        pmhs = (PMSLLHOOKSTRUCT)lp;
        if (Active[EXTS] && ExtendScreen(pmhs))
            return 1;
  }
    return CallNextHookEx(NULL, code, wp, lp);
}

void Input::setDesktopResolution(void)
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();

    GetWindowRect(hDesktop, &desktop);
    screenSize.x = desktop.right - 3;
    screenSize.y = desktop.bottom - 3;
}

void Input::Disable(void)
{
    UnhookWindowsHookEx(_kHook);
    UnhookWindowsHookEx(_mHook);
}

void Input::Enable(void)
{
    _kHook = SetWindowsHookEx(WH_KEYBOARD_LL, KbProc, NULL, 0);
    _mHook = SetWindowsHookEx(WH_MOUSE_LL, MsProc, NULL, 0);
}

void setActive(const unsigned char& act, const bool isActive)
{
    if (act == EnActive::INVXY)
    {
        Active[INVX] = isActive;
        Active[INVY] = isActive;
    }
    else
        Active[act] = isActive;
}
