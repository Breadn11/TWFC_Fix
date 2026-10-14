#include <windows.h>
#include <iostream>
#include <cstdio>

void WarnBox(const char* message)
{
	MessageBoxA(NULL, message, "Community Patch - Warning", MB_OK);
}

void ConsoleEnable()
{
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	freopen_s(&fp, "CONIN$", "r", stdin);
}