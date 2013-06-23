#pragma once

// Compilation Controlling Header Files:

#include "targetver.h"

// Windows Header Files:

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

#include <windows.h>

// Visual C++ Header Files:

#include <crtdbg.h>

// C++ Header Files:

#include <list>

// Project Header Files:

#include "ThreadInitializer.h"

// Types Definition:

struct INITIALIZER_INFO
{
	LPTHREAD_INITIALIZER_ROUTINE Initializer;
	LPTHREAD_INITIALIZER_CLEANUP Cleaner;
	LPVOID Context;
};

// Global Variables:

extern SRWLOCK g_srwHandlers;
extern std::list<INITIALIZER_INFO> InitializersInfo;
