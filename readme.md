## Installation
- Download the Win32 version of `d3d9.dll` from [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases).
- Place `d3d9.dll` into the game's Binaries folder.
- Go to [releases](https://github.com/Breadn11/TWFC_Fix/releases) and download the latest version of `CommunityPatch.asi`.
- Make a folder called `scripts` inside the game's Binaries folder, then place `CommunityPatch.asi` inside of it.

When installed, it'll automatically load with the game.

> [!WARNING]
> If you already have it installed and are updating to a new version, delete `CommunityPatch.ini` to generate new settings.

## Settings
To change settings - launch the game at least once, close it, then edit `CommunityPatch.ini` located in the scripts folder.

**fps**  
Controls the FPS cap.  
Recommended to keep at `60` to prevent minor physics issues.  
The game's default is `30`.

**desaturation_multiplier**  
A multiplier that controls the intensity of the game's desaturation filter.  
Set to `0` to completely remove the desaturation, `0.5` to halve the intensity, `9999` for black and white, etc.  
The game's default is `1`.

> [!IMPORTANT]
> Set a fix to `true` to enable it, `false` to disable it.

**fix_player_texture**  
Fixes a bug that causes the player's textures to load at half resolution.  

**fix_transform_invulnerability**  
Fixes a bug that causes most NPCs to be invulnerable while transforming.


## Credits
- [TWFC FPS Unlocker (Styx)](https://github.com/StyxSL/TWFC-FPS-Unlocker) - inspiration and fps cap offset
- WFC Runtime Inspector (kueblnn) - offsets
- [mINI](https://github.com/metayeti/mINI) - ini file handling



## Notes
- AI is used to reverse-engineer the cause of game bugs, everything else is done by hand.
- I plan to eventually make a complete community patch and package this with it, hence the naming inconsistencies.
- Feel free to contact me on Discord @ `.breadn`
