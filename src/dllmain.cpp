#include <windows.h>
#include <iostream>
#include "./mini/ini.h"
#include "./utils.h"
#include "./patches.h"

namespace config
{
	const wchar_t* moduleName = L"TWFC.exe";
	float fpsDesired = 60.0f;
}

bool HandleIni()
{
	mINI::INIFile file("scripts/CommunityPatch.ini");
	mINI::INIStructure ini;

	if (!file.read(ini))
	{
		ini["config"]["fps"] = "60";
		file.generate(ini);
	}

	std::string valRead = ini.get("config").get("fps");

	try 
	{
		config::fpsDesired = std::stof(valRead);
	}
	catch (...)
	{
		return 1;
	}

	return 0;
}

DWORD WINAPI MainThread(LPVOID)
{
	const DWORD baseAddress = GetModuleBaseAddress(config::moduleName);

	if (baseAddress == 0)
	{
		ErrorBox("failed to get module base address");
		return 1;
	}

	if (HandleIni() == 1)
	{
		ErrorBox("error reading or writing to CommunityPatch.ini");
		return 1;
	}

	if (patches::FPS(baseAddress, config::fpsDesired) == 1)
	{
		ErrorBox("default fps not detected as 30");
		return 1;
	}

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