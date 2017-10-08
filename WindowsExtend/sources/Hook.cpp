#include <Windows.h>

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