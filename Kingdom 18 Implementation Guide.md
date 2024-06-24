# Super Mario Odyssey: Kingdom 18 Mod - Implementation Guide

This guide contains a list of all necessary files and changes needed to manually implement an 18th custom kingdom into SMO using Exlaunch. This guide illustrates the steps for implementing an 18th kingdom unlocked after the 17 in the original game, but the steps can be extrapolated to implement a 19th or 20th kingdom (though this is untested). It may be feasible to implement a kingdom in-between existing kingdoms in the base game, but this would require much more work. If you use this in a mod, please credit [octember](https://github.com/octember8/SMO-Kingdom-18).

## RomFS

The GitHub repository mod uses the custom developer name `PuzzleWorld` for Kingdom 18. In all the following examples, `Puzzle` can be replaced with any custom developer name, as long as your naming scheme remains consistent. The example kingdom includes two stages, a main home stage `PuzzleWorldHomeStage` and a subarea stage `PuzzleWorldSubareaStage`.

### `LayoutData`

<details>
<summary>/LayoutData/WorldSelect.szs</summary>

This file contains the layout information of the world map select screen. First, `/layout.lyarc/blyt/WorldSelect.bflyt` must be edited to add the node pane group for the custom kingdom. 

Create a Null Pane, name it `World18` and place it in `/RootPane/All/World/Pos`. Set the size of the pane to `30 x 40`, and its position to `(684,0)` (each `WorldXX` pane is offset by 76 units). Set `Pane Visible` to false and `Influence transparency to children` to true.

Create another Null Pane, name it `ParWorld18` and make it a child of the `World18` pane. Set the size of the pane to `396.34 x 635.28`, and its position to `(0,0)`. Set `Pane Visible` to true and `Influence transparency to children` to true.

Create another Null Pane, name it `ParIcon18` and make it a child of the `World18` pane. Set the size of the pane to `31.2 x 52.3`, and its position to `(0,-46)`. Set `Pane Visible` to true and `Influence transparency to children` to true. Set `Part Scaling` to `Scaling`.

Note: Toolbox may export the .bflyt file incorrectly. If the world map layout does not appear correctly, use a hex editor to manually fix the file. Use this [bflyt documentation](https://mk8.tockdom.com/w/index.php?title=BFLYT_(File_Format)) to edit the values. The issue will likely be located in the `grp1` section, as it will be missing the `World18` pane. If you are using this for a custom 18th kingdom mod, it may just be easier to use the `WorldSelect.szs` file from the the repo to avoid this hassle.

---

Next, `/layout.lyarc/anim` includes the position and visibility for each node pane for all unlocking scenarios. `/layout.lyarc/anim/WorldSelect_WorldXX.bflan` contains the animation data for all the panes where `WorldXX` is the most recently unlocked kingdom. Note that there already exists a `WorldSelect_World18.bflan` file, this represents the postgame unlocking scenario where all kingdoms have been completed and the paths form a complete loop, connecting Darker Side to Mushroom Kingdom. All the .bflan files must be edited to include data for the `World18` pane. After editing the anim data, `WorldSelect_World19.bflan` will be the file used to represent the postgame unlock scenario.

Rename `WorldSelect_World18.bflan` to `WorldSelect_World19.bflan`. In the .bflan file, add an Animation Group to `Animation Info`, setting the Type as `Pane` and the name as `World18`. Add an Animation Group to that `World18` group, with Type `Visibility`. Add a Target to that `Visibility` group, with Target `Visibility` and Curve Type `Step`. Add a keyframe to the Target, setting the Slope as `0`, the Frame as `0` and the Value as `1`. Go to `/World/PaneSRT/ScaleX/Key Frame 0`, and set the Value to `0.8`. Go to `/World/PaneSRT/ScaleY/Key Frame 0`, and set the Value to `0.8`. Go to `/Pos/PaneSRT/TranslateX/Key Frame 0`, and set the Value to `-110`. Go to `/WinLine/PaneSRT/TranslateX/Key Frame 0`, and set the Value to `38`. In `Tag Info`, set both of the Frame values to `19`, the Animation Order to `20`, and the Name to `World19`.

The above process outlines the general steps to be repeated for each .bflan file. For all the other files (excluding `WorldSelect_Wait.bflan`, `WorldSelect_End.bflan`, `WorldSelect_TalkEnd.bflan`, `WorldSelect_TalkAppear.bflan`, `WorldSelect_Appear.bflan`), perform the following steps, which are similar to those above. In every .bflan file, add an Animation Group to `Animation Info`, setting the Type as `Pane` and the name as `World18`. Add an Animation Group to that `World18` group, with Type `Visibility`. Add a Target to that `Visibility` group, with Target `Visibility` and Curve Type `Step`. Add a keyframe to the Target, setting the Slope as `0` and the Value as `0`. The Frame number depends on the the `WorldXX` number of the .bflan file: `18 - 1 - XX`. So for `WorldSelect_World1.bflan`, the Frame would be `16`, and for `WorldSelect_World17.bflan`, the Frame would be `0`. For `WorldSelect_Test00.bflan`, assign the Key Frame data so Slope is `0`, Frame is `0`, and Value is `1`.

Finally, duplicate `WorldSelect_World17.bflan` and name the copy `WorldSelect_World18.bflan`. Set the Value of `/World/PaneSRT/ScaleX/Key Frame 0` and `/World/PaneSRT/ScaleY/Key Frame 0` to `0.8`. Set the Value of `/Pos/PaneSRT/TranslateX/Key Frame 0` to `-110`. Set the Value of `/WinLine/PaneSRT/TranslateX/Key Frame 0` to `38`. Set the Value of `/WinLine/PaneSRT/SizeX/Key Frame 0` to `1316`. For every other `WorldXX` pane, from `World1` to `World18`, subtract `1` from the Frame value of every Key Frame. Set the Value of `/World18/Visibility/Visibility/Key Frame 0` to `1`. Finally, in `Tag Info`, set both of the Frame values to `18`, the Animation Order to `19`, and the Name to `World18`.

Note: If you want to know where these numbers come from, the `/World/PaneSRT/Scale` values decrement by about `0.055` for each new kingdom unlock. For Darker Side, this value is `0.83`, but instead of `0.775` I rounded to `0.8` for a better fit. The `/Pos/PaneSRT/TranslateX` values decrease by `38` for each new kingdom unlock. Darker Side's value is `-72`, leading to the custom kingdom value of `-110`. The `/WinLine/PaneSRT/TranslateX` values increase by `38` for each new kingdom unlock. Darker Side's value is `0`, leading to the custom kingdom value of `38`. The `/Pos/PaneSRT/SizeX` values increase by `76` for each new kingdom unlock. Darker Side's value is `1240`, leading to the custom kingdom value of `1316`. The Visibility Key Frame Values (`0` or `1`) determines if each pane should be hidden or shown.

If you are implementing more than one new kingdom, use the above numbers to figure out the pane data Values for `WorldSelect_World19.bflan` and `WorldSelect_World20.bflan`. The Visibility data must be set such that any kingdoms with an index higher than the currently unlocked kingdom must be hidden (Visibility Value of `0`). Again, if you are only implementing a single new custom kingdom, it recommend to just use `WorldSelect.szs` file from the GitHub repo instead of doing all this finicky editing.
</details>

### `LocalizedData`

<details>
<summary>/LocalizedData/Common/ProjectData.szs</summary>

This file contains a .msbp file, which contains a list of all of the text files used in the game. In Toolbox, export `ProjectData.msbp`. In a dedicated .msbp editor, add the directories of any new custom text files; the example adds `StageMessage/Puzzle/PuzzleWorldHomeStage.mstxt` and `StageMessage/Puzzle/PuzzleWorldSubareaStage.mstxt`. Replace the .msbp file in Toolbox with the edited file.

</details>


The following files contain all the text data to be edited. This was only implemented for US English (`USen`) but the following steps can be repeated for other localizations.

<details>

<summary>/LocalizedData/USen/MessageData/StageMessage.szs</summary>

- `PuzzleWorldHomeStage.msbt`
  - This file contains the text for the custom kingdom stage, including moon names, location areas, etc. The use and editing of stage text files are explained in other modding guides and will not be covered here. These files can be created by duplicating and editing existing .msbt text files. These files should be named the same as the corresponding stage .szs file.
- `PuzzleWorldSubareaStage.msbt`
  - A stage text file should be created for every subarea stage containing text. 

</details>

<details>

<summary>/LocalizedData/USen/MessageData/SystemMessage.szs</summary>

- `WorldMap.msbt`
  - This file contains the text spoken by Cappy in the kingdom select menu. Add a new string `UnlockWorld_Puzzle` to add text for Cappy to say when unlocking the new custom kingdom. This text will have various unprintable characters for formatting (controlling the number of text boxes to cycle through), so it's recommended to copy the data from another `UnlockWorld` string, and changing the text to begin with `WorldMap016`, followed by the formatted text to be displayed in-game.
- `IconTag.msbt`
  - The game has a special font that renders the pictograms seen in text, including regional coin symbols and moon icons. This file contains the data for which symbols are used to represent each kingdom's regional coin and colored moon icons. Add a new string `CoinCollectIcon_Puzzle` and copy the data from the kingdom you want to have the regional coin icon from (if your kingdom does not have regional coins, a kingdom should still be chosen but it does not matter which). Add another new string `ShineIcon_Puzzle` and copy the data from a kingdom with the same colored moons as the custom kingdom.
- `StageMap.msbt`
  - This file contains the in-game name of all of the kingdoms. Add a new string `WorldName_Puzzle` and write the name of the kingdom (e.g. `Metro Kingdom`). Add another new string `RegionName_Puzzle` and write the name of the kingdom's region (e.g. `New Donk City`).
- `Tutorial.msbt`
  - This file is not strictly necessary, but it contains all the data for sign text (and also all the control guide text that pops up in-game). To add text for a new sign, add a new string named whatever you like, as long as it doesn't already exist (e.g. `ExampleSignText`). This string can contain no information, as it usually contains the data for control guide text that appears after reading a sign, which is not necessary. For the text that is actually displayed when reading a sign, add another new string named the same as the first, but append `_Explain` to the name (e.g. `ExampleSignText_Explain`). This text will have various unprintable characters for formatting (controlling the number of text boxes to cycle through), so it's recommended to copy the data from another `_Explain` string, and changing the `MoveWorldTipsXX` string for your own 13-character identifier and 2-digit number (e.g. `ExampleText__01`), followed by the formatted text to be displayed in-game.
- `StageMapMessage.msbt`
  - This file contains all the text displayed on the maps (brochures) for each kingdom. Many strings will be added in this file.
  - `TxtCaption00_Puzzle` contains the caption below the kingdom name in the top left corner of the map.
  - `TxtCaption01_Puzzle` to `TxtCaption05_Puzzle` contain the captions for each of the 5 images in the map.
  - `TxtCaption06_Puzzle` contains the caption for the small image in the bottom left corner of the map.
  - `TxtContents01_Puzzle` to `TxtContents05_Puzzle` contain the paragraphs of text associated with each of the 5 images in the map.
  - `TxtContents07_Puzzle` contains the "Three Keys to the Kingdom" numbered text in the bottom right the map.
  - `TxtData01_Puzzle` contains the "Population", "Size", and "Locals" information, each on a different line.
  - `TxtData02_Puzzle` contains the "Currency", "Industry", and "Temperature" information, each on a different line.
  - `TxtRegionCaption_Puzzle` contains the caption below the kingdom's region name.
  - `TxtTitle01_Puzzle` to `TxtTitle05_Puzzle` contain the titles for each of the 5 images in the map.
- `StageName.msbt`
  - This file contains nearly identical data as `StageMap.msbt`. Add a new string `WorldName_Puzzle` and write the name of the kingdom. Add another new string `RegionName_Puzzle` and write the name of the kingdom's region.

</details>

Note: Opening or viewing .msbt files in Toolbox may corrupt the values. It is instead recommended to export each .msbt file to be edited, modify its contents in a dedicated .msbt file editor, and then replace the original .msbt file in Toolbox.

### `MovieData`

<details>
<summary>/MovieData/World18.mp4</summary>

This file contains the preview video in the kingdom select menu for the new custom kingdom. It should be a .mp4 file with dimensions `640 x 352` and have no audio, but there are no specific restrictions on video length or framerate.
</details>

### `ObjectData`

<details>
<summary>/ObjectData/CubeMapPuzzleWorldHomeStage.szs</summary>

This file contains the cube map data for the `PuzzleWorldHomeStage` stage. Cube maps will not be covered in this guide (it may be easier to duplicate an existing cube map from the game). Don't forget to rename the .bfres file inside the .szs to `CubeMapPuzzleWorldHomeStage.bfres`.
</details>

<details>
<summary>/ObjectData/CubeMapPuzzleWorldSubareaStage.szs</summary>

Cube maps for all custom subarea stages should also be included (ensure the files are named correctly).
</details>

<details>
<summary>/ObjectData/HintPhoto.szs</summary>

This file is not necessary, but it contains preview textures for hint art. If your new kingdom includes custom hint art, replace `/HintPhoto.bfres/Textures/HintPhoto_alb.23` with a scaled-down image of your hint art (dimensions `320 x 180`). `HintPhoto_alb.23` to `HintPhoto_alb.26` are unused hint art images which can be overwritten.
</details>

<details>
<summary>/ObjectData/Texture2dMap.szs</summary>

This file contains the main images for each kingdom's map (the image with the large coordinate grid). This image has dimensions `2048 x 2048`, place the image into `/Texture2dMap.bfres/Textures` and name it `PuzzleWorldHomeStage`. If your kingdom has different maps for different scenarios, append the corresponding scenario number to each image. Each map also has a corresponding .byml file in the root directory of the file describing translation data to align the mario marker on the map. Duplicate an existing .byml file and rename it to `PuzzleWorldHomeStage.byml`. The `ProjMatrix`, `ViewMatrix` and `ProjViewMatrix` arrays control the scale and positioning of the map relative to the in-game coordinate system (Spotlight coordinate values are multiplied by 100 in the arrays).
</details>

<details>
<summary>/ObjectData/TextureHintPhotoOther11.szs</summary>

If your new kingdom has custom hint art, this file will contain the image (continuing the naming pattern used in Dark Side). Duplicate an existing `TextureHintPhotoXXX.szs` file and rename it (and the .bfres file inside it) to `TextureHintPhotoOther11`. Replace the image in `\TextureHintPhotoOther11.bfres\Textures` with the hint art image (dimensions `1280 x 720`) and name it `Other11`.
</details>

<details>
<summary>/ObjectData/TextureMapLayoutPuzzle.szs</summary>

This file contains the images for the custom kingdom's map. Duplicate an existing `TextureMapLayoutXXX.szs` file and rename it (and the .bfres file inside it) to `TextureMapLayoutPuzzle`. Replace the images in `\TextureMapLayoutPuzzle.bfres\Textures` with the following:
- `PuzzlePicImage00`: The large image in the top left of the map, behind the kingdom name (`1024 x 600`)
- `PuzzlePicImage01`: First captioned image (`440 x 512`)
- `PuzzlePicImage02`: Second captioned image (`440 x 240`)
- `PuzzlePicImage03`: Third captioned image (`504 x 432`)
- `PuzzlePicImage04`: Fourth captioned image (`440 x 472`)
- `PuzzlePicImage05`: Fifth captioned image (`440 x 232`)
- `PuzzlePicImage06`: The small image in the bottom left corner of the map (`64 x 64`)
- `PuzzlePicImage07`: The banner in the bottom right corner of the map (`1024 x 256`)
</details>

<details>
<summary>/ObjectData/TextureSaveData.szs</summary>

This file contains the images used in the save file icons. In `/TextureSaveData.bfres/Textures` add the save file image, with dimensions `160 x 90`, and rename it `PuzzleWorld00`. The number in the name represents which scenario uses the image; duplicate the image and rename the copy to `PuzzleWorld`. This new image is the image for the last scenario used by the custom kingdom. Some kingdoms instead have images ending in `ED` instead of a number, these represent World Peace scenarios, but any new custom kingdom would not need these images.
</details>

<details>
<summary>/ObjectData/TextureWorldMap.szs</summary>

When a kingdom is being unlocked for the first time in the world map, the preview video is replaced with a static preview image, contained in this file. In `/TextureWorldMap.bfres/Textures` add the preview image, with dimensions `640 x 352`, and rename it `PuzzlePicImage`.
</details>

<details>
<summary>/ObjectData/WorldMapEarth.szs</summary>

This file contains the globe and moon objects seen in the world map menu. The globe model contains a skeleton storing the point positions of the kingdoms on the world map. In `/WorldMapEarth.bfres/Models/WorldMapEarth/Skeleton/WorldMapEarth` create a new bone (duplicate an existing world bone) and name it `W18`. Change the position of the bone to point to where you want your kingdom to be located on the world map (preferably located between Darker Side and Mushroom Kingdom) And set the rotation accordingly. Set the bone's Index to `21` and turn `Scale One`, `Scale Uniform`, and `Scale Volume One` to true. If you want to add your custom kingdom to the globe's textures, go to `/WorldMapEarth.bfres/Textures` and edit the relevant `Earth_` texture files (or the `MoonBase_` texture files if your kingdom is placed on the moon).
</details>

You can also add files for custom objects to be used in your custom stage files, as with normal stage editing mods.

### `StageData`

<details>
<summary>/StageData/PuzzleWorldHomeStageMap.szs</summary>

This file contains the actual stage data for the custom kingdom. Stage editing will not be covered in this guide. The only things to note is that any new stage map file should match the name of the stage in the world list data, and any multi moon scenarios should match what is defined in the world list data.
</details>

<details>
<summary>/StageData/PuzzleWorldHomeStageDesign.szs</summary>

This file contains the design stage data for the custom kingdom. Ensure it is named correctly.
</details>

<details>
<summary>/StageData/PuzzleWorldSubareaStageMap.szs</summary>

Any number of subarea stages can be added to the custom kingdom. The stage map file name should match the corresponding entry in the world list data.
</details>

<details>
<summary>/StageData/PuzzleWorldSubareaStageDesign.szs</summary>

Every subarea stage should also have design stage data. Ensure it is named correctly.
</details>

### `SystemData`

<details>
<summary>/SystemData/CheckpointFlagInfo.szs</summary>

This file contains the checkpoint flag data for all kingdoms. Every kingdom has an associated .byml file in the root directory corresponding to every scenario. Duplicate one of these files and rename it to `FlagList_PuzzleWorldHomeStage_1.byml`. The .byml contains a `FlagList` array, where each entry contains a dictionary represents a checkpoint flag present in the scenario (if your kingdom has no checkpoints, this array can be left empty). These dictionaries contain a `FlagIdStr` element containing the stage obj ID of the checkpoint object, and a `Trans` element containing the position of the flag (with Spotlight coordinate values multiplied by 100). Add as many entries into the `FlagList` array as needed, and duplicate the created .byml for each scenario for the custom kingdom.
</details>

<details>
<summary>/SystemData/DemoChangeWorld.szs</summary>

This file contains the data for the time/weather environment seen in the cutscenes where the Odyssey travels between kingdoms. The file contains `GraphicsPreset.byml` which gives the enumeration for each environment (`0` for Day, `1` for Evening, `2` for Night, etc.). Open the other present file `WorldInfo.byml` and add a new entry to the end. This new entry should have a `DefaultGraphicsType` element (containing the enumeration for the chosen cutscene environment for the custom kingdom) and a `ScenarioInfo` element (which can just be set to null).
</details>

<details>
<summary>/SystemData/ItemList.szs</summary>

This file contains the collectible data for every kingdom. `\WorldItemTypeList.byml` contains the moon color and regional coin shape data for each kingdom (moon colors are represented by letters, and regional coin shapes are represented by numbers). Open this file and a new entry to the end. This entry should have a `CoinCollect` element (containing the letter representing the regional coin shape for your kingdom), a `Shine` element (containing the number representing the moon color for your kingdom), and a `WorldName` element (containing the kingdom name, e.g. `Puzzle`).
</details>

<details>
<summary>/SystemData/ShineInfo.szs</summary>

This file contains information about each kingdom's moons. Each .byml file contains a list of moons for every kingdom. Duplicate one of these .byml files and rename it `ShineList_PuzzleWorldHomeStage`. This .byml contains a `ShineList` array, containing dictionaries representing each moon in the kingdom. Add dictionary entries for every moon in the custom kingdom. These dictionaries will have the following entries:
- `HintIdx`: The order to request hints for moons, should the kingdom have a hint NPC
- `IsAchievement`: Is the moon an Archivist Toadette moon (set to false)
- `IsGrand`: Is the moon a multimoon
- `IsMoonRock`: Is the moon unlocked after hitting the moon rock
- `MainScenarioNo`: The quest number of the moon (set to `-1` if the moon is not part of an objective)
- `ObjId`: The stage obj ID of the moon
- `ObjectName`: Developer object notes (not necessary, just copy from an existing moon)
- `ProgressBitFlag`: The decimal representation of the bitflag determining which scenarios the moon is active in (copy from an existing moon)
- `ScenarioName`: Developer scenario notes (not necessary, just copy from an existing moon)
- `StageName`: The stage file the moon is located in (e.g. `PuzzleWorldSubareaStage`)
- `UniqueId`: A unique ID to given each moon (starting from 2000 should prevent overlaps)
- `Trans`: The position of the moon (with Spotlight coordinate values multiplied by 100)

Additionally, there is another .byml file `ShinePosList.byml` in the root directory. Add a dictionary entry for each custom moon, with a `UniqueId` element matching the one given in the above .byml file, and one or more elements labelled with numbers, representing the corresponding coordinates of the moon in each numbered scenario the moon exists in.

Moons that exist in subareas should be assigned the coordinates of the pipe/door in the main world home stage that leads to the subarea.
</details>

<details>
<summary>/SystemData/WorldList.szs</summary>

This file contains the list of kingdoms of the game; it's the most vital file to edit. Edit the following .byml files:
- `WorldListFromDb.byml`: Kingdom list
  - Add a dictionary entry with these elements:
    - `AfterEndingScenario`: The postgame scenario (set to `0`)
    - `ClearMainScenario`: The World Peace scenario (set to `0`)
    - `MoonRockScenario`: The scenario where the moon rock is unlocked (set to the stage's assigned moon rock scenario, else set to `0`)
    - `Name`: The custom kingdom's main stage name (set to `PuzzleWorldHomeStage`)
    - `ScenarioNum`: The number of scenarios for the kingdom
    - `WorldName`: The developer name of the kingdom (set to `Puzzle`)
    - `MainQuestInfo`: An array containing data for the kingdom's quests/objectives (set the array length to the number of kingdom scenarios and fill with `0`s)
    - `StageList`: An array of dictionaries storing every stage associated with the kingdom. Add an entry for every main or subarea stage, with an element `category` containing the type of stage (`MainStage`, `MainRouteStage`, or `ExStage`, etc.) and an element `name` containing the stage file name (e.g. `PuzzleWorldSubareaStage`)
- `StageLockList.byml`: Kingdom moon requirements
  - Add a dictionary entry to the `StageLockList` array with these elements:
    - `IsCountTotal`: Whether the moon requirement a total or relative to the last unlocked kingdom (set to true)
    - `IsCrash`: Whether the Odyssey crashes onto the custom kingdom (set to false)
    - `ShineNumInfo`: The number of moons needed to unlock the kingdom (set to any number, or to `880` as a 100% completion unlock)
- `StagePosList.byml`: Subarea stage positions
  - For every subarea stage in the custom kingdom, add a dictionary entry with the same name as the custom subarea. In each entry, add a dictionary containing the position of the subarea entrance from the main world home stage (with Spotlight coordinate values multiplied by 100). For every scenario this subarea is accessible, duplicate this coordinate dictionary and name each entry after its corresponding scenario number. For scenarios where the subarea is inaccessible, add an empty dictionary with the corresponding scenario number.
- `ExStageList.byml`: List of ExStage subareas
  - ExStage subareas are common stages containing a main moon and a secondary hidden moon. Add the names of any custom ExStage subareas to this file.
- `CollectCoinNum.byml`: Regional coin number list
  - This file contains a list of how many regional coins are in each kingdom. Add a dictionary entry with an element `CollectCoinNum` containing the number of regional coins for the custom kingdom, and an element `WorldName` containing the name of the kingdom.
- `WorldResource.byml`: Resource list
  - The function of this file is lesser known, but is assumed to contain a list of all resources loaded for each kingdom. Each dictionary entry contains a `WorldResource` array containing general objects to be loaded in each kingdom, and `ScenarioX` arrays containing objects loaded specifically for each scenario. It's recommended to copy a dictionary entry from a similar kingdom, and rename the entry's `WorldName` element to `Puzzle`. Then, remove and replace objects that do not need to be loaded for the custom kingdom with any other objects that should be loaded instead.
- `WorldList.byml`: Kingdoms List
  - Add a dictionary entry with these elements:
    - `AfterEndingScenario`: The postgame scenario (set to `0`)
    - `ClearMainScenario`: The World Peace scenario (set to `0`)
    - `MoonRockScenario`: The scenario where the moon rock is unlocked (set to the stage's assigned moon rock scenario, else set to `0`)
    - `Name`: The custom kingdom's main stage name (set to `PuzzleWorldHomeStage`)
    - `ScenarioNum`: The number of scenarios for the kingdom
    - `WorldName`: The developer name of the kingdom (set to `Puzzle`)
    - `MainQuestInfo`: An array containing data for the kingdom's quests/objectives (set the array length to the number of kingdom scenarios and fill with `0`s)
- `StageList.byml`: List of debug stages
  - Add a dictionary entry with an element `DevelopName` containing the world name for the custom kingdom, and an element `StageName` containing the name of the home stage.
- `CoinCollectList.byml`: Regional coin list
  - This file contains a list of every regional coin in the game. Add a dictionary entry to the `Table` array for every regional coin in the custom kingdom; having an element `ObjId`, containing the stage obj ID of the regional coin, an element `StageName`, containing the stage file name where the coin is located, and an element `UniqueId`, containing a unique given to each regional coin (starting from 2050 should prevent overlaps). The .byml root also contains a `UniqueIdMax` entry limiting the number of unique IDs; this value should be increased accordingly if the custom kingdom has any regional coins.

</details>



## ExeFS

### `main.cpp` Function Hooks

Note: World index is 0-indexed, so the index of Kingdom 18 would be 17, or 0x11.

<details>
<summary>WorldMovieResource</summary>

```c++
HOOK_DEFINE_INLINE(WorldMovieResource) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (ctx->X[23] == 0x110) {
            *(char**)(ctx->X[0]+ctx->X[23]) = "content:/MovieData/World18.mp4";
        } else {
            *(char**)(ctx->X[0]+ctx->X[23]) = (char*)ctx->X[8];
        }
    }
}
```
Inline hook at `0x508D70`. In the world map, each kingdom has a video preview, stored at `content:/MovieData/WorldXX.mp4`. The video file names are hardcoded, so the video resource name for World18 must be manually added in. If register X23 is equal to 0x10 multiplied by the index of the custom kingdom, load the corresponding video file name into the registers.

</details>

<details>
<summary>WorldMovieFirstTimeResource</summary>

```c++
HOOK_DEFINE_INLINE(WorldMovieFirstTimeResource) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (ctx->X[23] == 0x110) {
            ctx->X[2] = (long)"PuzzlePicImage";
        } else {
            ctx->X[2] = (long)*(char**)(ctx->X[8]+8);
        }
    }
}
```

Inline hook at `0x508D80`. When a kingdom is being unlocked for the first time in the world map, the preview video is replaced with a static preview image, stored in `content:/ObjectData/TextureWorldMap.szs`. These names are also hardcoded. If register X23 is equal to 0x10 multiplied by the index of the custom kingdom, load the corresponding image name from the `Textures` folder of the .szs file into the registers.

</details>

<details>
<summary>WorldMapRouteShuffle</summary>

```c++
HOOK_DEFINE_INLINE(WorldMapRouteShuffle) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (ctx->X[23] == 0x11) {
            ctx->W[9] = 0x11;
        } else {
            if (ctx->X[23] == 0x12) {
                ctx->W[9] = 0;
            } else {
                ctx->W[9] = ctx->W[23] - ctx->W[9];
            }
        }
    }
}
```
Inline hook at `0x50168C`. In the world map, this line of code determines which kingdom each WorldMapRoute (the yellow arc connecting kingdoms) connects to. If register X23 is equal to the index of the custom kingdom, load the index into register W9. If register X23 is equal to one more than the index of the custom kingdom (occurs when the world map connects in a complete loop), load 0 into register W9. Otherwise, load X23 - W9 into register W9.

</details>

<details>
<summary>CheckEnableUnlockWorldSpecial2and3</summary>

```c++
HOOK_DEFINE_TRAMPOLINE(CheckEnableUnlcokWorldSpecial2and3) {
    static bool Callback(al::LiveActor const* actor) {
        return checkEnableUnlockWorldSpecial3(actor) || Orig(actor);
    }
}

bool checkEnableUnlockWorldSpecial3(al::LiveActor const* actor) {
    bool foundShine[4];
    GameDataHolderAccessor gdha = GameDataHolderAccessor(actor);
    GameDataFile const* gdf = gdha.mData->mGameDataFile;

    unsigned long unlockFlag = gdf->isUnlockedWorld(0x10);
    if ((unlockFlag & 1) != 0) {
        unlockFlag = gdf->isUnlockedWorld(0x11);
        if ((unlockFlag & 1) == 0) {
            foundShine[0] = false;
            int unlockShineNum = gdf->findUnlockShineNumCurrentWorld(foundShine);
            if (!foundShine[0]) {
                return false;
            }
            int totalShines = gdf->getTotalPayShineNum();
            return unlockShineNum <= totalShines;
        }
    }
    return false;
}
```

Replacement hook at `0x52a794`. This code checks whether to unlock the custom kingdom (previous world must be unlocked, current world must be locked, required number of moons have been collected). Admittedly, this is a hacky fix. By treating the custom kingdom as Special3World, the hook takes advantage of how the game checks all the SpecialX kingdoms for unlocking simultaneously. Additionally, the game doesn't distinguish which kingdom returned `true` for the unlock check, the game just unlocks the next available kingdom. This way, the hook combines with the Special2World check, returning `true` if either kingdom is unlockable, which the game does not distinguish. The first `gdf->isUnlockedWorld(X)` should pass the index of the world unlocked before the custom kingdom, and the second `gdf->isUnlockedWorld(X)` should pass the index of the custom kingdom.

</details>

<details>
<summary>MoonRockCheck</summary>

```c++
HOOK_DEFINE_TRAMPOLINE(MoonRockCheck) {
    static int Callback(GameDataFile* gdf, int index) {
        if (index == 0x11) {
            return 0;
        }
        return Orig(gdf, index);
    }
}
```
Trampoline hook at `0x526A24`. If the custom kingdom does not contain a moon rock, then the "Current Objective" system will glitch out. Since most kingdoms in the game contain moon rocks, the few exceptions are hardcoded. If the custom kingdom contains a moon rock, this hook can be ignored. If the index parameter is the index of the custom kingdom lacking a moon rock, return 0.

Note: The "Current Objective" of custom kingdoms can only be viewed within the custom kingdom, whereas in the original game, the objective for a kingdom can be viewed in all previous kingdoms.

</details>

### `patches.cpp` Patches

<details>
<summary>List of Patches</summary>

- World Map Points & Routes Initialization
  - 0x50065C: `mov W0, 0x90`
    - Allocate an array for each WorldMapPoint Actor (0x12 * 0x8)
  - 0x500844: `cmp X26, 0x12`
    - Create 18 WorldMapPoint actors
  - 0x5008D0: `mov W0, 0x90`
    - Allocate an array for each WorldMapRoute Actor (0x12 * 0x8)
  - 0x50096C: `cmp X26, 0x12`
    - Create 18 WorldMapRoute actors
  - 0x5008F4: `mov W24, 0x2AC2B`
    - Bitmask controlling whether each kingdom uses a small or large WorldMapRoute. (0x2AC2B = 0b101010110000101011)
- World Map Layout Actors Initialization
  - 0x5009FC: `mov W21, 0x90`
    - Allocate an array for each WorldSelect ParWorld LayoutActor (0x12 * 0x8)
  - 0x500B18: `mov W21, 0x12`
    - Allocate an array for each WorldSelect ParIcon LayoutActor (0x12 * 0x8)
- World Map Index Adjustment
  - 0x5006BC: `add W0, W27, 0x13`
    - Fix index selection cycle
  - 0x5006C0: `mov W1, 0x12`
    - Fix index selection cycle
  - 0x500B20: `mov W0, 0x48`
    - Allocate an array for actor coordinates
- World Map Load Actors
  - 0x500D98: `cmp X20, 0x90`
    - Load 18 WorldMapPoint Actors (0x12 * 0x8)
  - 0x500DE0: `cmp X20, 0x90`
    - Load 18 WorldMapRoute Actors (0x12 * 0x8)
- World Map Appear Limit
  - 0x501244: `cmp W0, 0x12`
    - Limit number of unlocked worlds to at most 18
  - 0x501248: `mov W26, 0x12`
    - Limit number of unlocked worlds to at most 18
- World Map Appear Check Unlocks
  - 0x5012DC: `cmp W8, 0x12`
    - Check if all kingdoms are unlocked
  - 0x501320: `cmp W8, 0x12`
    - Check if all kingdoms are unlocked
- World Map Show/Hide Actors
  - 0x5015FC: `cmp X20, 0x12`
    - Show/Hide each of the 18 Actors
- World Map Kill
  - 0x5022B0: `cmp X20, 0x90`
    - Kill all 18 Actors
- World Movie Initialization
  - 0x508D30: `mov W0, 0x120`
    - Allocate an array for each movie texture (0x12 * 0x10)
  - 0x508DA8: `cmp X24, 0x12`
    - Create 18 movie textures

</details>

## Save Files

When opening a save file in the mod, new entries are automatically added into the save data. This means that any save files opened with the mod turned on will permanently affect its data. Here is a list of all save data entries modified by the mod, in the extreme case you need to modify it further or remove any changes caused by opening the mod (however it is recommended to avoid save editing and just back-up unaffected save files).

<details>
<summary>Save File Data Entries</summary>

- `Checkpoint`
  - An array where every entry corresponds to an activated checkpoint flag, given the name of the stage it is located in, and the object id of the flag within the stage.
- `GameProgressData`
  - `IsFirstTimeWorld`
    - Booleans for the first visit of each kingdom; the 18th entry corresponds to kingdom 18
  - `UnlockWorldNum`
    - Index of most recently unlocked kingdom
- `GetCoinCollectData`
  - An array of all regional coins, given its unique ID, and whether it has been collected or not
- `HintPhotoData`
  - An array of all hint arts that have been viewed
- `IsPayShineAllInAllWorld`
  - Have all the moons been collected (excluding extra shopping moons)
- `MoonRockData`
  - `IsAppearedMoonRockTalkMessage`
    - Booleans for whether Cappy has pointed out the moon rock in each kingdom; the 18th entry corresponds to kingdom 18
  - `IsShowDemoMoonRockMapWorld`
    - Booleans for whether the moon rock map message has been displayed; the 18th entry corresponds to kingdom 18
  - `IsShowDemoOpenMoonRockWorld`
    - Booleans for whether the moon rock opening cutscene has played; the 18th entry corresponds to kingdom 18
- `NextWorldId`
  - The index of the kingdom after the current kingdom
- `PrevWorldId`
  - The index of the kingdom before the current kingdom
- `SequenceDemoSkipData`
  - `WorldData`
    - A list of arrays for whether the kingdom travel cutscenes has been viewed; the 18th array corresponds to kingdom 18
- `ShineData`
  - An array of all moons and their collection data
- `StageName`
  - Name of the stage that Mario is currently in
- `VisitData`
  - A list of all visited ExStage subareas
- `WorldId`
  - The index of the world that Mario is currently in
- `WorldInfo`
  - A list of arrays for each kingdom's data; the 18th array corresponds to kingdom 18

</details>