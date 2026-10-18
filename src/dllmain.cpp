#include <windows.h>
#include <iostream>
#include "./mini/ini.h"
#include "./utils.h"
#include "./patches.h"

namespace config
{
	const std::string iniFile = "scripts/CommunityPatch.ini";
	const wchar_t* moduleName = L"TWFC.exe";
	
	bool debug = false;
	float fpsDesired = 60.0f;
	float desaturationMulti = 1.0f;
	bool doTextureFix = true;
	bool doTransformFix = true;
}

bool HandleIni()
{
	mINI::INIFile file(config::iniFile);
	mINI::INIStructure ini;

	if (!file.read(ini))
	{
		ini["config"]["fps"] = "60";
		ini["config"]["desaturation_multiplier"] = "1";
		ini["config"]["fix_player_texture"] = "true";
		ini["config"]["fix_transform_invulnerability"] = "true";
		ini["advanced"]["debug"] = "false";
		
		if (!file.generate(ini, true))
		{
			return 1;
		}
	}

	std::string valRead_fps = ini.get("config").get("fps");
	std::string valRead_sat = ini.get("config").get("desaturation_multiplier");
	std::string valRead_texFix = ini.get("config").get("fix_player_texture");
	std::string valRead_invulnFix = ini.get("config").get("fix_transform_invulnerability");
	std::string valRead_debug = ini.get("advanced").get("debug");

	try 
	{
		config::debug = StrToBool(valRead_debug);
		config::fpsDesired = std::stof(valRead_fps);
		config::desaturationMulti = std::stof(valRead_sat);
		config::doTextureFix = StrToBool(valRead_texFix);
		config::doTransformFix = StrToBool(valRead_invulnFix);
	}
	catch (...)
	{
		return 1;
	}

	return 0;
}

DWORD WINAPI MainThread(LPVOID)
{
	if (HandleIni() == 1)
	{
		ErrorBox("error reading or writing CommunityPatch.ini, this may be fixed by deleting it and trying again");
		return 1;
	}

	if (config::debug){ConsoleEnable();}
	
	// todo: use GetModuleHandleW instead
	const DWORD baseAddress = GetModuleBaseAddress(config::moduleName);

	if (baseAddress == 0)
	{
		ErrorBox("failed to get module base address");
		return 1;
	}
	
	if (config::fpsDesired != 30.0f && config::fpsDesired != 0.0f)
	{
		if (patches::FPS(baseAddress, config::fpsDesired) == 1)
		{
			ErrorBox("failed to change fps cap, default fps not detected as 30");
			return 1;
		}
	}

	if (config::doTextureFix)
	{
		if (patches::PlayerTexture(baseAddress) == 1)
		{
			ErrorBox("failed to apply player texture fix");
			return 1;
		}
	}
	
	// todo: swap to using memcpy to change exactly 6 bytes instead of 8
	if (config::doTransformFix)
	{
		if (patches::TransformInvuln(baseAddress) == 1)
		{
			ErrorBox("failed to apply transformation invincibility fix");
			return 1;
		}
	}

	// todo: find alternative, this property doesn't affect cutscenes
	
	// keep this function last cuz no threading for sleeps
	if (config::desaturationMulti != 1.0f)
	{
		if (patches::Desaturation(baseAddress, config::desaturationMulti) == 1)
		{
			ErrorBox("failed to change desaturation");
			return 1;
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