#include <windows.h>

namespace patches {

bool FPS(DWORD baseAddress, float fpsDesired)
{
	DWORD fpsAddress = baseAddress + 0x2103F30;

	if (*(float*)(fpsAddress) != 30.0f)
	{
		return 1;
	}
	else
	{
		*(float*)fpsAddress = fpsDesired;
		return 0;
	}
}

}