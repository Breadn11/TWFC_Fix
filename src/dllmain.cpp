#include <windows.h>
#include <iostream>
#include "./mini/ini.h"
#include "./utils.h"
#include "./patches.h"

namespace config
{
	const std::string iniFile = "scripts/CommunityPatch.ini";
	const wchar_t* moduleName = L"TWFC.exe";
	float fpsDesired = 60.0f;
}

bool HandleIni()
{
	mINI::INIFile file(config::iniFile);
	mINI::INIStructure ini;

	if (!file.read(ini))
	{
		ini["config"]["fps"] = "60";
		
		if (!file.generate(ini))
		{
			return 1;
		}
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