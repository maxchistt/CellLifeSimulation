# CellLifeSimulation

Project of 2D cell life simulation with C++ and C#

I realised it with MVC pattern

There are five projects here :

- C++ static library for simulation model
- C++/CLR DLL wrapper
- Qt C++ client
- WPF C# client
- Web C# ASP.NET / Angular client

This project depends from C3D Toolkit!

If you have it, you need to:

- Copy folder "QtVision" with QtVision static libray built from [this](https://github.com/maxchistt/QtVision-Static-Class-Library) (tag v1.1) project into solution folder
- Copy "Kernel" and "Vision" distribution folders into solution folder into "C3D" subfolder
- Define actual licence key and licence signature in "C3D_USAGE.h" file in "QtCellLifeSimulationApp" project
- Uncomment "`#define C3D_USAGE`" in "C3D_USAGE.h" file in "QtCellLifeSimulationApp" project
- Add "c3dvision.lib;c3d.lib;qtvision.lib;" to additional dependencies of "QtCellLifeSimulationApp" project in project settings

![WPF](https://i.postimg.cc/YCcTkCyb/image.png)

![Qt](https://i.postimg.cc/DZcR4smk/image.png)

![ASP.NET](https://i.postimg.cc/R0vbwhtc/image.png)

Inspired by [OnigiriScience](https://www.youtube.com/c/OnigiriScience)
