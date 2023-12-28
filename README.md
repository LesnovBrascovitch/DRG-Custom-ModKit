## DRG-Custom-ModKit
This project is based on Buckminsterfullerene02's ModKit, Currently this project is quite work-in-progress. It should be useful for animation and weapon related modding at the moment.  
This Mod Kit recreated some C++ codes and materials, BPs, animations, anim notifies etc to make some modding(such as animation, custom weapon, player character related) easier.  
You can make DRG mod in the editor and migrate to DRG without using additional framework(If you use recreated C++ source's functions).  

Also this project has some helper BPs, such as Vanity testing, Victory Pose Player, Editor Utility Blueprints to test, edit things easily.
## Packaging
DRG-Custom-ModKit/_Package/_SamsPackerTemplate must be used for this project. Only this packer can compile your mod and UE's compile and other packing tools don't work with this project at all.
You can use EUBP_SamPacker to make never cooked folder paths and WhiteList and BlackList paths.

When you firstly compile, it would take time. After that, packaging time shouldn't be problem with using never cooked paths. (For exsample, packaging DoomShotgun folder would take less than 1 min with i5-2500k, RTX 3060, RAM24Gb, SSD)

## Notes
- You can't make executable with this project, migrating assets to another project would cause collapted asset(Not mod assets you make, only DRG's assets).
- Currently including many sources from various modders to make it faster to understand how the DRG's function works. (These might be removed in the future)
- Other modder's DRG sources are moved to under _DRGModding folder.
- DRGLib produces many errors in the editor. (Might fix in the future)

## Tutorials

## Credits

- [Assembly Storm's DRG Sources](https://github.com/trumank/drg-mods)
- [Buckminsterfullerene02's Community-Modkit](https://github.com/DRG-Modding/Community-Modkit)
- [Fancyneer's Animation Assets](https://mod.io/u/fancyneer)
- [GoldBlade's ModHub and DRG Sources](https://github.com/GoldBlade77/DRG-Mods/tree/main)
- [Hlomida's Boscochan Assets](https://mod.io/g/drg/u/hlomida)
- [Samamster's DRGLib](https://github.com/SamsDRGMods/DRGLib)


Developed with Unreal Engine 4
