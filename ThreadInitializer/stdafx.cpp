#include "stdafx.h"

SRWLOCK g_srwHandlers = SRWLOCK_INIT;
std::list<HANDLERSINFO> g_handlers;
