#pragma once

#include <windows.h>

DWORD GetModuleBaseAddress(const wchar_t* processName);

void ErrorBox(const char* message);

void ConsoleEnable();

bool StrToBool(std::string input);