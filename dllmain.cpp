#include <windows.h>
#include "./memory.h"
#include "./utils.h"

DWORD WINAPI MainThread(LPVOID)
{
	const wchar_t* moduleName = L"TWFC.exe";
	
	const DWORD baseAddress = GetModuleBaseAddress(moduleName);

	if (baseAddress == 0)
	{
		WarnBox("failed to get module base address");
		return 0;
	}

	return 1;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		HANDLE hThread = CreateThread(NULL, 0, MainThread, NULL, 0, NULL);
		
		if (hThread == NULL)
		{
			return FALSE;
		}
		CloseHandle(hThread);
	}
	return TRUE;
}