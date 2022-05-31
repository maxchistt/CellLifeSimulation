# CellLifeSimulation

Project of 2D cell life simulation with C++ and C#

I realised it with MVC pattern

There are five projects here :

- C++ static library for simulation model
- C++/CLR DLL wrapper
- Qt C++ client
- WPF C# client
- Web C# ASP.NET / Angular client

At first, need to set up your VS for working with Qt to build this project.

This project depends from C3D Toolkit! You can launch it without C3D, but, if you have it, you need to:

- Copy folder "QtVision" with QtVision static libray, built from [this](https://github.com/maxchistt/QtVision-Static-Class-Library) project by running "QtVision.Export.ps1", into solution folder
- Copy "Kernel" and "Vision" distribution folders into solution folder into "C3D" subfolder
- Uncomment "`#define C3D_USAGE`" in "C3D_USAGE.h" file in "QtCellLifeSimulationApp" project
- Add "c3dvision.lib;c3d.lib;QtVision.lib;" to additional dependencies of "QtCellLifeSimulationApp" project in project settings

![WPF](https://i.postimg.cc/tCrvnCpt/image.png)

![Qt](https://i.postimg.cc/DZcR4smk/image.png)

![ASP.NET](https://i.postimg.cc/90yR5f13/image-2.png)

Inspired by [OnigiriScience](https://www.youtube.com/c/OnigiriScience)
