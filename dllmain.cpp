#include <windows.h>
#include "./memory.h"

#include <string>

const wchar_t* moduleName = L"TWFC.exe";

DWORD WINAPI MainThread(LPVOID)
{
	

	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		HANDLE hThread = CreateThread(NULL, 0, MainThread, NULL, 0, NULL);
		
		if (hThread == NULL)
		{
			// message box
		}
		else
		{
			CloseHandle(hThread);
		}
	}
	return TRUE;
}