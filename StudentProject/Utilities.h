// Provides utility definitions for the Langton's Ant project.
// Includes memory leak detection support for Visual Studio Debug builds
// and a simple Cell struct representing the state of each grid cell.

#pragma once

 // Memory Leak Detection for Visual Studio (Debug Mode)
#if defined _MSC_VER && defined _DEBUG
#include <crtdbg.h>

// Override new operator to track file and line number allocations
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

// Enable leak detection flags: track memory leaks at program exit
#define ENABLE_LEAK_DETECTION() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#else
    // For other compilers or non-debug builds, do nothing
#define ENABLE_LEAK_DETECTION()
#endif

// Simple struct to represent a Cell's state in the grid
struct Cell
{
    bool isAlive;  // true if cell is alive, false if dead
};