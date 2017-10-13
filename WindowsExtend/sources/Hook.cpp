#include <Windows.h>

typedef enum
{
	NONE = 0x00,
	LOW,
	HIGH
} CrossedState;


static POINT screenSize;

static char	qwerty[2][26] =
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

void setDesktopResolution(void)
{
	RECT desktop;

	// Gettimg a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	
	// Gettimg  the size of screen
	GetWindowRect(hDesktop, &desktop);
	screenSize.x = desktop.right - 3;
	screenSize.y = desktop.bottom - 3;
}

LRESULT CALLBACK KbProc(int code, WPARAM wp, LPARAM lp)
{
	static bool wasSent = FALSE;
	PKBDLLHOOKSTRUCT	p;

	/* Getting only "down" events */
	if ((wp == WM_KEYDOWN || wp == WM_SYSKEYDOWN) && code == HC_ACTION)
	{
		if (wasSent == TRUE)
		{
			wasSent = FALSE;
			return CallNextHookEx(NULL, code, wp, lp);
		}
		p = (PKBDLLHOOKSTRUCT)lp;

		/* Converting azerty to qwerty */
		for (unsigned char i = 0; i < 26; ++i)
		{
			if (p->vkCode == qwerty[0][i])
			{
				wasSent = TRUE;
				keybd_event(qwerty[1][i], 0, 0, 0);
				return 1;
			}
		}
	}
	return CallNextHookEx(NULL, code, wp, lp);
}

LRESULT CALLBACK MsProc(int code, WPARAM wp, LPARAM lp)
{
	PMSLLHOOKSTRUCT	pmhs;
	static char XCrossed = NONE;
	static char YCrossed = NONE;
	POINT p;
	
	if (code == HC_ACTION && wp == WM_MOUSEMOVE)
	{
		pmhs = (PMSLLHOOKSTRUCT)lp;

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
			return 1;
	}
	return CallNextHookEx(NULL, code, wp, lp);
}
