#include <windows.h>
#include <iostream>
#include <cstdio>

void ErrorBox(const char* message)
{
	MessageBoxA(NULL, message, "Community Patch - Error", MB_OK | MB_ICONERROR | MB_TOPMOST);
}

void ConsoleEnable()
{
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	freopen_s(&fp, "CONIN$", "r", stdin);
}