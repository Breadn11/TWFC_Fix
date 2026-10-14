#include <windows.h>
#include <iostream>
#include "./memory.h"
#include "./utils.h"

namespace config
{
	const wchar_t* moduleName = L"TWFC.exe";
	const float fpsDesired = 120.0f;
}

DWORD WINAPI MainThread(LPVOID)
{
	const DWORD baseAddress = GetModuleBaseAddress(config::moduleName);

	if (baseAddress == 0)
	{
		ErrorBox("failed to get module base address");
		return 1;
	}

	DWORD fpsAddress = baseAddress + 0x2103F30;

	if (*(float*)(fpsAddress) != 30.0f)
	{
		ErrorBox("default fps not detected as 30");
		return 1;
	}

	*(float*) fpsAddress = config::fpsDesired;

	return 0;
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