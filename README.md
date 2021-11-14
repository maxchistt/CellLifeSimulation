# CellLifeSimulation

Project of 2D cell life simulation with C++ and C#

I realised it with MVC pattern

There are six projects here :

- C++ static library for simulation model
- C++/CLR DLL wrapper
- Qt C++ client
- WPF C# client
- Web C# ASP.NET / Angular client
- QtVision (Additional project for C3D usage)

This project depends from C3D Toolkit!

If you had it, you need to:

- Copy Kernel and Vision distributions into "C3D" folder
- Define actual licence key and licence signature in "C3D_USAGE.h" file in "QtCellLifeSimulationApp" project

Else, if you haven't access to C3D:

- Delete "`#define C3D_USAGE`" in "C3D_USAGE.h" file in "QtCellLifeSimulationApp" project
- Open configuration manager and disable "QtVision" build
- Delete "c3d.lib" and "c3dvision.lib" from additional dependencies of "QtCellLifeSimulationApp" project
- Delete "QtVision" dependency "QtCellLifeSimulationApp" project links
- Or you can only switch to commit with v1.3 tag

![WPF](https://i.postimg.cc/YCcTkCyb/image.png)

![Qt](https://i.postimg.cc/DZcR4smk/image.png)

![ASP.NET](https://i.postimg.cc/R0vbwhtc/image.png)

Inspired by [OnigiriScience](https://www.youtube.com/c/OnigiriScience)
