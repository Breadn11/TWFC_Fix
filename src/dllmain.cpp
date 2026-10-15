#include <windows.h>
#include <iostream>
#include "./mini/ini.h"
#include "./utils.h"
#include "./patches.h"

namespace config
{
	const std::string iniFile = "scripts/CommunityPatch.ini";
	const wchar_t* moduleName = L"TWFC.exe";
	float fpsDesired = 30.0f;
	bool doTextureFix = true;
	float desaturationMulti = 1.0f;
}

bool HandleIni()
{
	mINI::INIFile file(config::iniFile);
	mINI::INIStructure ini;

	if (!file.read(ini))
	{
		ini["config"]["fps"] = "60";
		ini["config"]["player_texture_fix"] = "true";
		ini["config"]["desaturation_multiplier"] = "1";
		
		if (!file.generate(ini, true))
		{
			return 1;
		}
	}

	std::string valRead_fps = ini.get("config").get("fps");
	std::string valRead_tex = ini.get("config").get("player_texture_fix");
	std::string valRead_sat = ini.get("config").get("desaturation_multiplier");

	try 
	{
		config::fpsDesired = std::stof(valRead_fps);
		config::doTextureFix = StrToBool(valRead_tex);
		config::desaturationMulti = std::stof(valRead_sat);
	}
	catch (...)
	{
		return 1;
	}

	return 0;
}

DWORD WINAPI MainThread(LPVOID)
{
	// todo: use GetModuleHandleW instead
	const DWORD baseAddress = GetModuleBaseAddress(config::moduleName);

	//ConsoleEnable();

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
	
	if (config::fpsDesired != 30.0f && config::fpsDesired != 0.0f)
	{
		if (patches::FPS(baseAddress, config::fpsDesired) == 1)
		{
			ErrorBox("failed to apply fps patch, default fps not detected as 30");
			return 1;
		}
	}

	if (config::doTextureFix)
	{
		if (patches::PlayerTexture(baseAddress) == 1)
		{
			ErrorBox("failed to apply player texture patch");
			return 1;
		}
	}

	if (config::desaturationMulti != 1.0f)
	{
		if (patches::Desaturation(baseAddress, config::desaturationMulti) == 1)
		{
			ErrorBox("failed to apply desaturation patch");
		}
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