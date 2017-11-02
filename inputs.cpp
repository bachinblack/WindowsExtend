#include "inputs.h"
#include <QDebug>

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

bool Input::ExtendScreen(POINT& pos)
{
    POINT           p;

    p = pos;
    if (pos.x <= 2)
        pos.x = screenSize.x;
    else if (pos.x >= screenSize.x)
        pos.x = 3;

    if (pos.y <= 2)
        pos.y = screenSize.y;
    else if (pos.y >= screenSize.y)
        pos.y = 3;

    //SetCursorPos(pmhs->pt.x, pmhs->pt.y);
    if (p.x != pos.x || p.y != pos.y)
        return true;
    return false;
}

void Input::InvertX(POINT& pos)
{
    static short last = -5000;
    short diff = pos.x - last;

    if (last != -5000)
        last = last - diff;
    else
        last = screenSize.x - pos.x;
    if (last < 5)
        last = 5;
    if (last > screenSize.x - 2)
        last = screenSize.x - 2;
    pos.x = last;
}

void Input::InvertY(POINT& pos)
{
    static short last = -5000;
    short diff = pos.y - last;

    if (last != -5000)
        last = last - diff;
    else
        last = screenSize.y - pos.y;
    if (last < 5)
        last = 5;
    if (last > screenSize.y - 2)
        last = screenSize.y - 2;
    pos.y = last;
}

LRESULT CALLBACK Input::MsProc(int code, WPARAM wp, LPARAM lp)
{
    PMSLLHOOKSTRUCT	pmhs;
    POINT           pos;
    LRESULT         ret = CallNextHookEx(NULL, code, wp, lp);

    if (Active[ALL]) { qDebug() << "disabled"; return ret; }
    if (code == HC_ACTION && wp == WM_MOUSEMOVE)
    {
        pmhs = (PMSLLHOOKSTRUCT)lp;
        pos = pmhs->pt;
        if (Active[EXTS] && ExtendScreen(pos))
            ret = 1;
        if (Active[INVX] || Active[INVY]) {
            InvertX(pos);
            ret = 1;
        } if (Active[INVY]) {
            InvertY(pos);
            ret = 1;
        }
        if (ret == 1)
           SetCursorPos(pos.x, pos.y);
  }
    return ret;
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
    if (!_disable) {
        _disable = true;
        UnhookWindowsHookEx(_kHook);
        UnhookWindowsHookEx(_mHook);
    }
}

void Input::Enable(void)
{
    if (_disable) {
        _disable = false;
        _kHook = SetWindowsHookEx(WH_KEYBOARD_LL, KbProc, NULL, 0);
        _mHook = SetWindowsHookEx(WH_MOUSE_LL, MsProc, NULL, 0);
    }
}

void setActive(const unsigned char& act, const bool isActive)
{
    Active[act] = isActive;
}
