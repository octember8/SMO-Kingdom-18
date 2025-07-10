# Super Mario Odyssey: Kingdom 18 Mod

This is the repository for Super Mario Odyssey: Kingdom 18, a mod implementing an additional 18th kingdom into Super Mario Odyssey, in comparison to the original game's 17 kingdoms. This mod is chiefly aimed towards mod developers, providing examples and documentation as to how to use and implement an 18th kingdom into your own mods. This mod is for SMO v1.0 only.

## Save Files
***This mod uses a custom save file system. Save files affected by this mod will be incompatible without this mod.*** Opening the mod will automatically create a `/smo/Kingdom18` directory at the root of the SD card to store these custom save files. Use this directory if you wish to edit/swap any Kingdom 18 save file. If a save file from this directory containing Kingdom 18 data is loaded when the mod is turned off, the game will not open (this can only happen by moving a save file from this directory to your default save directory). **It is strongly recommended to back-up all your save files anyway before using this mod, and to not move any affected save files in the custom directory.** A 100% save file, excluding Kingdom 18 progress, is provided in the repo.


## Build Instructions

<details>

<summary>Developer build instructions</summary>

  ### Building Prerequisites

  - [devkitPro](https://devkitpro.org/) 
  - Python 3
  - The [Keystone-Engine](https://www.keystone-engine.org/) Python Module

  ### Building

  Build has only been tested on WSL2 running Ubuntu 20.04.1.

  Just run:
  ```
  DEVKITPRO={path_to_devkitpro} make
  ```

  On Ubuntu (and other Debian-based systems), devkitPro will be installed to `/opt/devkitpro` by default:

  ```
  DEVKITPRO=/opt/devkitpro/ make
  ```

</details>

## Mod Implementation Guide

A guide for manually implementing new kingdoms has been included in the repo, `Kingdom 18 Implementation Guide.md`. This file contains a comprehensive list of all RomFS and ExeFS changes needed so that you can implement your own custom 18th kingdom from scratch. If you will instead create a custom kingdom mod by editing the example files in the repo, this guide can also be used to indicate which files you should change.

## Credits
- [Shadow](https://github.com/shadowninja108/exlaunch) - Exlaunch & Hardware troubleshooting
- [CraftyBoss](https://github.com/CraftyBoss/SMO-Exlaunch-Base) - SMO Exlaunch Base & Spinning emoji video
- [LynxDev](https://github.com/LynxDev2) - Custom save file system & ExeFS help
- Slycer - RomFS help
- [MonsterDruide1](https://github.com/MonsterDruide1/OdysseyDecomp/tree/master) - Extra help
- chico88959 - Extra help