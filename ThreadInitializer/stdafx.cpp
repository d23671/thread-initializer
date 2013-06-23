#include "stdafx.h"

SRWLOCK g_srwHandlers = SRWLOCK_INIT;
std::list<INITIALIZER_INFO> g_handlers;
