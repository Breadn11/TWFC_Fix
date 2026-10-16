#include <windows.h>
#include <iostream>

// print raw hex at address:
// std::cout << std::hex << *(uint64_t*)addr << "\n";

namespace patches {


bool FPS(DWORD baseAddress, float fpsDesired)
{
	DWORD addrFPS = baseAddress + 0x2103F30;

	if (*(float*)addrFPS != 30.0f)
	{
		return 1;
	}
	
	*(float*)addrFPS = fpsDesired;
	return 0;
}

bool PlayerTexture(DWORD baseAddress)
{
	DWORD addrMat = baseAddress + 0x2EC1BC;
	DWORD addrTex = baseAddress + 0x2EC22E;

	if (*(BYTE*)addrMat != 0x6E || *(BYTE*)addrTex != 0x01)
	{
		return 1;
	}

	DWORD oldProtection{};

	if (!VirtualProtect((LPVOID)addrMat, 0x73, PAGE_EXECUTE_READWRITE, &oldProtection))
	{
		return 1;
	}

	*(BYTE*)addrMat = 0x5E;
	*(BYTE*)addrTex = 0x00;

	DWORD unused{};
	VirtualProtect((LPVOID)addrMat, 0x73, oldProtection, &unused);

	return 0;
}

bool Desaturation(DWORD baseAddress, float newDesatMulti)
{
	int attempts{};
	
	while (true)
	{
		attempts++;

		// failsafe - if someone takes more than 20 sec to load the game, they have bigger problems
		if (attempts > 20){return 1;}
		//std::cout << attempts << "\n";

		Sleep(1000);
		
		DWORD addrDesat = baseAddress + 0x2210968;
		
		addrDesat = *(DWORD*)addrDesat;
		if (addrDesat == 0){continue;}

		addrDesat += 0x350;

		addrDesat = *(DWORD*)addrDesat;
		if (addrDesat == 0){continue;}

		addrDesat = *(DWORD*)addrDesat;
		if (addrDesat == 0){continue;}
		
		addrDesat += 0x3C;

		*(float*)addrDesat = newDesatMulti;
		return 0;
	}
}


bool TransformInvuln(DWORD baseAddress)
{
	DWORD addr = baseAddress + 0x2C1214;

	if (*(uint64_t*)addr != 0x8b550000014b850f)
	{
		return 1;
	}

	DWORD oldProtection{};
	if (!VirtualProtect((LPVOID)addr, 0x16, PAGE_EXECUTE_READWRITE, &oldProtection))
	{
		return 1;
	}
	
	*(uint64_t*)addr = 0x8B55909090909090;

	DWORD unused{};
	VirtualProtect((LPVOID)addr, 0x16, oldProtection, &unused);

	return 0;
}


}