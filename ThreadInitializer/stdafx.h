#pragma once

// Compilation Controlling Header Files:

#include "targetver.h"

// Windows Header Files:

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

#include <windows.h>

// C++ Header Files:

#include <list>

// Project Header Files:

#include "ThreadInitializer.h"

// Types Definition:

struct HANDLERSINFO
{
	LPTHREAD_INITIALIZER_ROUTINE pfnInitializer;
	LPTHREAD_INITIALIZER_CLEANUP pfnCleanup;
	LPVOID lpContext;
};

// Global Variables:

extern SRWLOCK g_srwHandlers;
extern std::list<HANDLERSINFO> g_handlers;
