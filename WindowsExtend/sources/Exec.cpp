#include <Exec.hpp>

std::unordered_map < std::list<VKCode>, LPCSTR > *Shortcuts;

VOID Exec(LPCTSTR lpApplicationName)
{
	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// start the program up
	if (!CreateProcess(lpApplicationName,   // the path
		NULL,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	))
		OutputDebugStringW(L"Failed to start process.\n");

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

bool	checkShortcut()
{
	return true;
}

void	FillExecList(void)
{
	std::ifstream	fs("shortcuts.data");
	
	//Shortcuts = new std::unordered_map<std::list<VKCode>, LPCSTR>;
	//	{97, L"C:/Program Files (x86)/Google/Chrome/Application/chrome.exe"}
}