#include <windows.h>
#include <TlHelp32.h>

DWORD GetModuleBaseAddress(const wchar_t* processName)
{
	HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, GetCurrentProcessId());

	if (hProcessSnapshot == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD moduleBaseAddr = 0;

	MODULEENTRY32 moduleEntry{};
	moduleEntry.dwSize = sizeof(moduleEntry);

	BOOL hasEntry = Module32First(hProcessSnapshot, &moduleEntry);

	while (hasEntry)
	{
		if (_wcsicmp(moduleEntry.szModule, processName) == 0)
		{
			moduleBaseAddr = (DWORD)moduleEntry.modBaseAddr;
			break;
		}
		hasEntry = Module32Next(hProcessSnapshot, &moduleEntry);
	}

	CloseHandle(hProcessSnapshot);
	return moduleBaseAddr;
}