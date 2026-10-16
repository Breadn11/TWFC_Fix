## Installation
- Download the Win32 version of `d3d9.dll` from [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases).
- Place `d3d9.dll` into the game's Binaries folder.
- Download `CommunityPatch.asi` from this repository's releases.
- Make a folder called `scripts` inside the game's Binaries folder, then place `CommunityPatch.asi` inside of it.

When installed, it'll automatically load with the game.


## Settings
To change settings - launch the game at least once, close it, then edit `CommunityPatch.ini` located in the scripts folder.

**fps**  
Controls the FPS cap.  
Recommended to keep at `60` to prevent minor physics issues.  
The game's default is `30`.

**player_texture_fix**  
Fixes a bug that causes the player's textures to load at half resolution.  
Set to `true` to enable the fix, `false` to disable it.

**desaturation_multiplier**  
A multiplier that controls the intensity of the game's desaturation filter.  
Set to `0` to completely remove the desaturation, `0.5` to half the intensity, `9999` for black and white, etc.  
The game's default is `1`.



## Credits
- [TWFC FPS Unlocker (Styx)](https://github.com/StyxSL/TWFC-FPS-Unlocker) - inspiration and fps cap offset
- WFC Runtime Inspector (kueblnn) - offsets
- [mINI](https://github.com/metayeti/mINI) - ini file handling



## Notes
- AI is used to reverse-engineer the cause of some game bugs, everything else is done by hand.
- I plan to eventually make a complete community patch and package this with it, hence the naming inconsistencies.
- Feel free to contact me on Discord @ `.breadn`