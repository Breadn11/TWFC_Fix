#pragma once

#include <windows.h>

namespace patches 
{


bool FPS(DWORD baseAddress, float fpsDesired);

bool PlayerTexture(DWORD baseAddress);


}