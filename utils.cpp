#include <windows.h>

void WarnBox(const char* message)
{
	MessageBoxA(NULL, message, "Community Patch - Warning", MB_OK);
}